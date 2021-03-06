/*

  Amit Kanwar - akanwar2
  Mohit Goyal - mgoyal
  Deepak Prashanth - dprasan
  Key Value System
  Copyright (C) 2016 Hung-Wei Tseng, Ph.D. <hungwei_tseng@ncsu.edu>

  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  This code is derived from function prototypes found /usr/include/fuse/fuse.h
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  His code is licensed under the LGPLv2.
  A copy of that code is included in the file fuse.h
  
  The point of this FUSE filesystem is to provide an introduction to
  FUSE.  It was my first FUSE filesystem as I got to know the
  software; hopefully, the comments in this code will help people who
  follow later to get a gentler introduction.

*/

#include "kvfs.h"
#include "log.h"
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif

char *str2md5_kvfs(const char *str, int length) {  //Copied from kvfs.c to alleviate double hashing
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);
    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }
    return out;
}

static int kvfs_error(char *str) {
    log_msg("Error: %s: %s\n", strerror(errno), str);
    return -errno;
}

static void kvfs_fullpath(char *fpath, const char *path) {
    strcpy(fpath, KVFS_DATA->rootdir);
    if (!strcmp(path, "6666cd76f96956469e7be39d750cc7d9")) {
        return;
    } else {
        sprintf(fpath, "%s/%s", fpath, path);
    }
    //sprintf (fpath, "%s", path);
    return;
}

///////////////////////////////////////////////////////////
//
// Prototypes for all these functions, and the C-style comments,
// come from /usr/include/fuse.h
//
/** Get file attributes.
 *
 * Similar to stat().  The 'st_dev' and 'st_blksize' fields are
 * ignored.  The 'st_ino' field is ignored except if the 'use_ino'
 * mount option is given.
 */

int kvfs_getattr_impl(const char *path, struct stat *statbuf)
{
    DIR *dir;
    struct dirent *rdr;
    char fpath[PATH_MAX];
	int retvalue;
    char dummy[PATH_MAX];

    /*kvfs_fullpath(fpath, path);
    log_msg("   kvfs_getattr - fpath: %s, statbuf: 0x%08x\n", fpath, statbuf);
    retvalue = lstat(fpath, statbuf);
    if (retvalue != 0) {
        return kvfs_error("Unable to get attributes");
    }
    log_stat(statbuf);
    return retvalue; */
    dir = opendir(KVFS_DATA->rootdir);
    if (!(strcmp(path, "6666cd76f96956469e7be39d750cc7d9"))) {
        return lstat(KVFS_DATA->rootdir, statbuf);
    }
    log_msg("   kvfs_getattr - fpath: %s, statbuf: 0x%08x\n", path, statbuf);
    while((rdr = readdir(dir)) != NULL) {
        memset(dummy, '\0', sizeof(dummy));
        strcpy(dummy, "/");
        strcat(dummy, rdr->d_name);
        if (!strcmp(rdr->d_name, path)) { 
              kvfs_fullpath(fpath, rdr->d_name);
              retvalue = lstat(fpath, statbuf);
              //statbuf->st_mode = statbuf->st_mode || 0000;
              //log_stat(statbuf);
			  closedir(dir);
              return retvalue;
        }

        if (!strcmp(str2md5_kvfs(dummy, strlen(dummy)), path)) {
            kvfs_fullpath(fpath, rdr->d_name);
            retvalue = lstat(fpath, statbuf);
            //freopen("stderr_log", "w", stderr);
            //freopen("stdout_log", "w", stdout);
            //errno = 0;
			closedir(dir);
            return retvalue;
        }
    }
	closedir(dir);
    kvfs_fullpath(fpath, path);
    retvalue = lstat(fpath, statbuf);
    if (retvalue < 0) {
        return kvfs_error("Unable to get attributes\n");
    }
    return retvalue;
}

/** Read the target of a symbolic link
 *
 * The buffer should be filled with a null terminated string.  The
 * buffer size argument includes the space for the terminating
 * null character.  If the linkname is too long to fit in the
 * buffer, it should be truncated.  The return value should be 0
 * for success.
 */
// Note the system readlink() will truncate and lose the terminating
// null.  So, the size passed to to the system readlink() must be one
// less than the size passed to kvfs_readlink()
// kvfs_readlink() code by Bernardo F Costa (thanks!)
int kvfs_readlink_impl(const char *path, char *link, size_t size)
{
    size_t len;
    char fpath[PATH_MAX];
    char flink[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    kvfs_fullpath(flink, link);
    log_msg("   kvfs_readlink - fpath: %s, link: %s, size: %d, len: %d\n", 
            fpath, flink, size, len);
    
    if ((len = readlink(fpath, flink, size-1)) < 0) {
        return kvfs_error("Unable to read the target of symbolic link");
    }

    if (len == size) {
        log_msg("Truncation might have occured.\n");
    }
	if (len >= 0) {
	    link[len] = '\0';
		len = 0;
	}

    return len;
}

/** Create a file node
 *
 * There is no create() operation, mknod() will be called for
 * creation of all non-directory, non-symlink nodes.
 */
// shouldn't that comment be "if" there is no.... ?
int kvfs_mknod_impl(const char *path, mode_t mode, dev_t dev)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_mknod - fpath: %s, mode: 0%3o, dev: %lld\n", 
            fpath, mode, dev);
    retvalue = mknod(fpath, mode, dev);
    if (retvalue != 0) {
        return kvfs_error("Unable to create a file node");
    }
    return retvalue;
}

/** Create a directory */
int kvfs_mkdir_impl(const char *path, mode_t mode)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_mkdir - fpath: %s, mode: 0%3o\n", fpath, mode);
    if (retvalue = mkdir (fpath, mode) < 0) {
        return kvfs_error("Unable to create a directory");
    }
    return retvalue;
}

/** Remove a file */
int kvfs_unlink_impl(const char *path)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_unlink - fpath: %s\n", fpath);
    if ((retvalue = unlink(fpath)) < 0) {                       //Second chance to the file as the call might be hindered because of double hashing
		
    	DIR *dir;
    	struct dirent *rdr;
    	char dummy[PATH_MAX];
		dir = opendir(KVFS_DATA->rootdir);
		while(rdr = readdir(dir)){                         
			memset(dummy, '\0', sizeof(dummy));
        	strcpy(dummy, "/");
		    strcat(dummy, rdr->d_name);
			log_msg("%s %s",dummy,path);
			if (!strcmp(str2md5_kvfs(dummy, strlen(dummy)), path)) {
				kvfs_fullpath(fpath, rdr->d_name);
				closedir(dir);
				if(retvalue = unlink(fpath)<0){
        			return kvfs_error("Unable to remove a file");
				}
				return retvalue;
			}
		}
		closedir(dir);
        return kvfs_error("Unable to remove a file");
	}
    return retvalue;
}


/** Remove a directory */
int kvfs_rmdir_impl(const char *path)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_rmdir - fpath: %s\n", fpath);
    if ((retvalue = rmdir(fpath)) < 0) {
    	DIR *dir;									//This code is to handle a case of double hashing. For example, it will happen in case of rmdir *
    	struct dirent *rdr;
    	char dummy[PATH_MAX];
		dir = opendir(KVFS_DATA->rootdir);
		while(rdr = readdir(dir)){
			memset(dummy, '\0', sizeof(dummy));
        	strcpy(dummy, "/");
		    strcat(dummy, rdr->d_name);
			log_msg("%s %s",dummy,path);
			if (!strcmp(str2md5_kvfs(dummy, strlen(dummy)), path)) {
				kvfs_fullpath(fpath, rdr->d_name);
				closedir(dir);
				if(retvalue = rmdir(fpath)<0){
        			return kvfs_error("Unable to remove directory");
				}
				return retvalue;
			}
		}
		closedir(dir);
        return kvfs_error("Unable to remove directory");
    }
    return retvalue;
}

/** Create a symbolic link */
// The parameters here are a little bit confusing, but do correspond
// to the symlink() system call.  The 'path' is where the link points,
// while the 'link' is the link itself.  So we need to leave the path
// unaltered, but insert the link into the mounted directory.
int kvfs_symlink_impl(const char *path, const char *link)
{
    char fpath[PATH_MAX];
    char flink[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    kvfs_fullpath(flink, link);
    log_msg(    "kvfs_symlink - fpath: %s, link: %s\n", fpath, flink);
    if ((retvalue = symlink(path, flink)) < 0) {
        return kvfs_error("Unable to create symbolic link");
    }
    return retvalue;
}

/** Rename a file */
// both path and newpath are fs-relative
int kvfs_rename_impl(const char *path, const char *newpath)
{
    char fpath[PATH_MAX];
    char fnewpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    kvfs_fullpath(fnewpath, newpath);
    log_msg(    "kvfs_rename - fpath: %s, fnewpath: %s\n", fpath, fnewpath);
    if ((retvalue = rename(fpath, fnewpath)) < 0) {
        return kvfs_error("Unable to rename file");
    }
    return retvalue;
}

/** Create a hard link to a file */
int kvfs_link_impl(const char *path, const char *newpath)
{
    char fpath[PATH_MAX];
    char fnewpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    kvfs_fullpath(fnewpath, newpath);
    log_msg("   kvfs_link - fpath: %s, fnewpath: %s\n", fpath, fnewpath);
    if ((retvalue = link(fpath, fnewpath)) < 0) {
        return kvfs_error("Unable to create hard link to file");
    }
    return retvalue;
}

/** Change the permission bits of a file */
int kvfs_chmod_impl(const char *path, mode_t mode)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_chmod - fpath: %s, mode: 0%3o\n", fpath, mode);
    if ((retvalue = chmod(fpath, mode)) < 0) {
        return kvfs_error("Unable to change the permissions of file");
    }
    return retvalue;
}

/** Change the owner and group of a file */
int kvfs_chown_impl(const char *path, uid_t uid, gid_t gid)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_chown - fpath: %s, uid: %d, gid: %d\n", fpath, uid, gid);
    if ((retvalue = chown(fpath, uid, gid)) < 0) {
        return kvfs_error("Unable to change the owner and group of file");
    }
    return retvalue;
}

/** Change the size of a file */
int kvfs_truncate_impl(const char *path, off_t newsize)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_truncate - fpath: %s, newsize: %lld\n", fpath, newsize);
    if ((retvalue = truncate(fpath, newsize)) < 0) {
        return kvfs_error("Unable to change the size of file");
    }
    return retvalue;
}

/** Change the access and/or modification times of a file */
/* note -- I'll want to change this as soon as 2.6 is in debian testing */
int kvfs_utime_impl(const char *path, struct utimbuf *ubuf)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_utime - fpath: %s, utimbuf: 0x%08x\n", fpath, ubuf);
    if ((retvalue = utime(fpath, ubuf)) < 0) {
        return kvfs_error("Unable to change the access/modification time");
    }
    return retvalue;
}

/** File open operation
 *
 * No creation, or truncation flags (O_CREAT, O_EXCL, O_TRUNC)
 * will be passed to open().  Open should check if the operation
 * is permitted for the given flags.  Optionally open may also
 * return an arbitrary filehandle in the fuse_file_info structure,
 * which will be passed to all file operations.
 *
 * Changed in version 2.2
 */
int kvfs_open_impl(const char *path, struct fuse_file_info *fi)
{
    int fd;
    char fpath[PATH_MAX];
	int retvalue = 0;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_open - fpath: %s, fuse_file_info: 0x%08x\n", fpath, fi);
    if ((fd = open(fpath, fi->flags)) < 0) {
        return kvfs_error("Unable to open file");
    }
    fi->fh = fd;
    log_fi(fi);
    return retvalue;
}

/** Read data from an open file
 *
 * Read should return exactly the number of bytes requested except
 * on EOF or error, otherwise the rest of the data will be
 * substituted with zeroes.  An exception to this is when the
 * 'direct_io' mount option is specified, in which case the return
 * value of the read system call will reflect the return value of
 * this operation.
 *
 * Changed in version 2.2
 */
// I don't fully understand the documentation above -- it doesn't
// match the documentation for the read() system call which says it
// can return with anything up to the amount of data requested. nor
// with the fusexmp code which returns the amount of data also
// returned by read.
int kvfs_read_impl(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    int retvalue;
    log_msg("   kvfs_read - fpath: %s, fuse_file_info: 0x%08x\n", path, fi);
    log_fi(fi);
    if ((retvalue = pread(fi->fh, buf, size, offset)) < 0) {
       return kvfs_error("Unable to read file");
    } 
    return retvalue;
}

/** Write data to an open file
 *
 * Write should return exactly the number of bytes requested
 * except on error.  An exception to this is when the 'direct_io'
 * mount option is specified (see read operation).
 *
 * Changed in version 2.2
 */
// As  with read(), the documentation above is inconsistent with the
// documentation for the write() system call.
int kvfs_write_impl(const char *path, const char *buf, size_t size, off_t offset,
	     struct fuse_file_info *fi)
{
    int retvalue, fd;
    char fpath[PATH_MAX];
	log_msg("   kvfs_write - fpath: %s, fuse_file_info: 0x%08x\n", path, fi);
    log_fi(fi);
    
    if((retvalue = pwrite(fi->fh, buf, size, offset)) < 0) {
        return kvfs_error("Unable to write file");
    }
    return retvalue;
}

/** Get file system statistics
 *
 * The 'f_frsize', 'f_favail', 'f_fsid' and 'f_flag' fields are ignored
 *
 * Replaced 'struct statfs' parameter with 'struct statvfs' in
 * version 2.5
 */
int kvfs_statfs_impl(const char *path, struct statvfs *statv)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_statfs - fpath: %s, statvfs: 0x%08x\n", fpath, statv);
    if ((retvalue = statfs(fpath, statv)) < 0) {
        return kvfs_error("Unable to get file system statistics");
    }
    log_statvfs(statv);
    return retvalue;
}

/** Possibly flush cached data
 *
 * BIG NOTE: This is not equivalent to fsync().  It's not a
 * request to sync dirty data.
 *
 * Flush is called on each close() of a file descriptor.  So if a
 * filesystem wants to return write errors in close() and the file
 * has cached dirty data, this is a good place to write back data
 * and return any errors.  Since many applications ignore close()
 * errors this is not always useful.
 *
 * NOTE: The flush() method may be called more than once for each
 * open().  This happens if more than one file descriptor refers
 * to an opened file due to dup(), dup2() or fork() calls.  It is
 * not possible to determine if a flush is final, so each flush
 * should be treated equally.  Multiple write-flush sequences are
 * relatively rare, so this shouldn't be a problem.
 *
 * Filesystems shouldn't assume that flush will always be called
 * after some writes, or that if will be called at all.
 *
 * Changed in version 2.2
 */
// this is a no-op in BBFS.  It just logs the call and returns success
int kvfs_flush_impl(const char *path, struct fuse_file_info *fi)
{
    int retvalue;
    log_msg("\nkvfs_flush(path=\"%s\", fi=0x%08x)\n", path, fi);
    // no need to get fpath on this one, since I work from fi->fh not the path
    retvalue = fsync(fi->fh);
    log_fi(fi);
	
    return retvalue;
}

/** Release an open file
 *
 * Release is called when there are no more references to an open
 * file: all file descriptors are closed and all memory mappings
 * are unmapped.
 *
 * For every open() call there will be exactly one release() call
 * with the same flags and file descriptor.  It is possible to
 * have a file opened more than once, in which case only the last
 * release will mean, that no more reads/writes will happen on the
 * file.  The return value of release is ignored.
 *
 * Changed in version 2.2
 */
int kvfs_release_impl(const char *path, struct fuse_file_info *fi)
{
    int retvalue;
	log_msg("   kvfs_release - fpath: %s, fi: 0x%08x\n", path, fi);
    log_fi(fi);
    if ((retvalue = close(fi->fh)) < 0) {
        return kvfs_error("Unable to release open file");
    }
    return retvalue;
}

/** Synchronize file contents
 *
 * If the datasync parameter is non-zero, then only the user data
 * should be flushed, not the meta data.
 *
 * Changed in version 2.2
 */
int kvfs_fsync_impl(const char *path, int datasync, struct fuse_file_info *fi)
{
    int retvalue;
	log_msg("   kvfs_fsync - fpath: %s, datasync: %d, fuse_file_info: 0x%08x\n", 
            path, datasync, fi);
    log_fi(fi);
    if ((retvalue = fsync(fi->fh)) < 0) {
        return kvfs_error("Unable to synchronize file contents");
    }
    return retvalue;
}

#ifdef HAVE_SYS_XATTR_H
/** Set extended attributes */
int kvfs_setxattr_impl(const char *path, const char *name, const char *value, size_t size, int flags)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    if ((retvalue = setxattr(fpath, name, value, size, flags)) < 0) {
        return kvfs_error("Unable to set extended attributes");
    }
    return retvalue;
}

/** Get extended attributes */
int kvfs_getxattr_impl(const char *path, const char *name, char *value, size_t size)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    if ((retvalue = getxattr(fpath, name, value, size)) < 0) {
        return kvfs_error("Unable to get extended attributes");
    }
    return retvalue;
}

/** List extended attributes */
int kvfs_listxattr_impl(const char *path, char *list, size_t size)
{
    char fpath[PATH_MAX];
	int revalue;

    kvfs_fullpath(fpath, path);
    if ((retvalue = listattr(fpath, list, size)) < 0) {
        return kvfs_error("Unable to list extended attributes");
    }
    return retvalue;
}

/** Remove extended attributes */
int kvfs_removexattr_impl(const char *path, const char *name)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    if ((retvalue = removexattr(fpath, name)) < 0) {
        return kvfs_error("Unable to remove extended attributes");
    }
    return retvalue;
}
#endif

/** Open directory
 *
 * This method should check if the open operation is permitted for
 * this  directory
 *
 * Introduced in version 2.3
 */
int kvfs_opendir_impl(const char *path, struct fuse_file_info *fi)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_opendir - fpath: %s, fuse_file_info: 0x%08x\n", fpath, fi);
    log_fi(fi);
    if ((retvalue = chdir(KVFS_DATA->rootdir)) < 0) { //since there is no concept of directories here, we change the directory to this
        return kvfs_error("Unable to open directory.\n");
    }
  /*  if (!strcmp(fpath, path)) {
        if (retvalue = chdir(fpath) < 0) {
            return kvfs_error("Unable to open directory");
        }
    } else {
        // No need to change directory as every file is absolute
        return 0;
    }  */
    return retvalue;
}

/** Read directory
 *
 * This supersedes the old getdir() interface.  New applications
 * should use this.
 *
 * The filesystem may choose between two modes of operation:
 *
 * 1) The readdir implementation ignores the offset parameter, and
 * passes zero to the filler function's offset.  The filler
 * function will not return '1' (unless an error happens), so the
 * whole directory is read in a single readdir operation.  This
 * works just like the old getdir() method.
 *
 * 2) The readdir implementation keeps track of the offsets of the
 * directory entries.  It uses the offset parameter and always
 * passes non-zero offset to the filler function.  When the buffer
 * is full (or an error happens) the filler function will return
 * '1'.
 *
 * Introduced in version 2.3
 */

int kvfs_readdir_impl(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
	       struct fuse_file_info *fi)
{
    DIR *dir;
    struct dirent *rdr;
    char fpath[PATH_MAX];
    struct stat statbuf;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_readdir - fpath: %s, filler: 0x%08x, fuse_file_info: 0x%08x\n", 
            fpath, filler, fi);
    log_fi(fi);
    //log_filler(filler);
    if (1) {
        dir = opendir(fpath); 
        while ((rdr = readdir(dir)) != NULL) {
            //kvfs_getattr_impl(rdr->d_name, &statbuf);
            filler(buf, rdr->d_name, NULL, 0);
        }
    }
    log_msg("Exiting readdir\n");
    return 0;
}

/** Release directory
 *
 * Introduced in version 2.3
 */
int kvfs_releasedir_impl(const char *path, struct fuse_file_info *fi)
{
    log_msg("   kvfs_releasedir - fpath: %s, fuse_file_info: 0x%08x\n", path, fi);
    log_fi(fi);
	int retvalue;
    if ((retvalue = close(fi->fh)) < 0) {
        return kvfs_error("Unable to release directory");
    }
    return retvalue;
}

/** Synchronize directory contents
 *
 * If the datasync parameter is non-zero, then only the user data
 * should be flushed, not the meta data
 *
 * Introduced in version 2.3
 */
// when exactly is this called?  when a user calls fsync and it
// happens to be a directory? ??? >>> I need to implement this...
int kvfs_fsyncdir_impl(const char *path, int datasync, struct fuse_file_info *fi)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_fsyncdir - fpath: %s, fuse_file_info: 0x%08x\n", fpath, fi);
    // Will think in the last...Don't really know what happens here
    return 0;
}

int kvfs_access_impl(const char *path, int mask)
{
    char fpath[PATH_MAX];
	int retvalue;

    kvfs_fullpath(fpath, path);
    log_msg("   kvfs_access - fpath: %s, mask: %d", fpath,  mask);
    if ((retvalue = access(fpath, mask)) < 0) {
    	DIR *dir;									//This code is to handle a case of double hashing. For example, it will happen in case of rm *
    	struct dirent *rdr;
    	char dummy[PATH_MAX];
		dir = opendir(KVFS_DATA->rootdir);
		while(rdr = readdir(dir)){
			memset(dummy, '\0', sizeof(dummy));
        	strcpy(dummy, "/");
		    strcat(dummy, rdr->d_name);
			log_msg("%s %s",dummy,path);
			if (!strcmp(str2md5_kvfs(dummy, strlen(dummy)), path)) {
				kvfs_fullpath(fpath, rdr->d_name);
				closedir(dir);
				if(retvalue = access(fpath, mask)<0){
        			return kvfs_error("Unable to access path");
				}
				return retvalue;
			}
		}
		closedir(dir);
        return kvfs_error("Unable to access path");
	}
    return retvalue;
}

/**
 * Create and open a file
 *
 * If the file does not exist, first create it with the specified
 * mode, and then open it.
 *
 * If this method is not implemented or under Linux kernel
 * versions earlier than 2.6.15, the mknod() and open() methods
 * will be called instead.
 *
 * Introduced in version 2.5
 */
// Not implemented.  I had a version that used creat() to create and
// open the file, which it turned out opened the file write-only.

/**
 * Change the size of an open file
 *
 * This method is called instead of the truncate() method if the
 * truncation was invoked from an ftruncate() system call.
 *
 * If this method is not implemented or under Linux kernel
 * versions earlier than 2.6.15, the truncate() method will be
 * called instead.
 *
 * Introduced in version 2.5
 */
int kvfs_ftruncate_impl(const char *path, off_t offset, struct fuse_file_info *fi)
{
	int retvalue;

    log_msg("   kvfs_ftruncate - fpath: %s, fuse_file_info: 0x%08x\n", path, fi);
    log_fi(fi);
    if ((retvalue = ftruncate(fi->fh, offset)) < 0) {
        return kvfs_error("Unable to do ftruncate");
    }
    return 0;
}

/**
 * Get attributes from an open file
 *
 * This method is called instead of the getattr() method if the
 * file information is available.
 *
 * Currently this is only called after the create() method if that
 * is implemented (see above).  Later it may be called for
 * invocations of fstat() too.
 *
 * Introduced in version 2.5
 */
int kvfs_fgetattr_impl(const char *path, struct stat *statbuf, struct fuse_file_info *fi)
{
    int retvalue;
    log_msg("   kvfs_fgetattr - fpath: %s, statbuf: 0x%08x, fuse_file_info: 0x%08x\n", 
            path, statbuf, fi);
    log_fi(fi);
    if ((retvalue = fstat(fi->fh, statbuf)) < 0) {
        return kvfs_error("Unable to get attributes from open file");
    }
    log_stat(statbuf);
    return retvalue;
}

