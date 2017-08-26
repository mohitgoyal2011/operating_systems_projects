import os,sys
import statistics
import commands

def measure_ram_access():
	for i in [1024, 2048, 16*1024, 32*1024, 64*1024, 128*1024, 256*1024, 1024*1024, 1024*1024*2, 1024*1024*3, 1024*1024*4, 1024*1024*8, 1024*1024*64, 1024*1024*128, 1024*1024*256]:
		output = commands.getoutput('./ram_access ' + str(i) + ' >data_file' )
		data_file = open('data_file','r')
		lines = data_file.readlines()
		clock_cycles = []
		for line in lines:
			if len(line.split(' ')) == 3:
				clock_cycles.append(int(line.split(' ')[2]))
		print "RAM Access Time",statistics.mean(clock_cycles), i

def measure_cpu_performance():
	output = commands.getoutput('./measure_cpu_performance > data_file' )
	data_file = open('data_file','r')
	lines = data_file.readlines()
	clock_cycles = []
	for line in lines:
		if len(line.split(' ')) == 3:
			clock_cycles.append(int(line.split(' ')[2]))
	print "CPU Speed",statistics.mean(clock_cycles)

def measure_performance_measure_overhead():
	output = commands.getoutput('./measure_performance_measure_overhead > data_file' )
	data_file = open('data_file','r')
	lines = data_file.readlines()
	clock_cycles = []
	for line in lines:
		if len(line.split(' ')) == 3:
			clock_cycles.append(int(line.split(' ')[2]))
	print "Performance Overhead",statistics.mean(clock_cycles)
	
def measure_procedure_call():
	output = commands.getoutput('./procedure_call_test > data_file' )
	data_file = open('data_file','r')
	lines = data_file.readlines()
	clock_cycles = []
	counter = 0
	for line in lines:
		if " * * *" in line:
			print "Procedure Call", counter ,statistics.mean(clock_cycles)
			counter = counter + 1
			clock_cycles = []
			continue
		if len(line.split(' ')) == 3:
			clock_cycles.append(int(line.split(' ')[2]))
