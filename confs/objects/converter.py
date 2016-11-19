import sys

file_format_info =\
'''\
#Simplified .obj file format
#c gives info on counts `v vn f`
#v denotes a vertex, a vec3
#vn denotes a normal
#f denotes a face. Consists of 3 vertices, followed by the normal
'''

def to_rt(filename):
	try:
		f = open(filename, 'r')
		f = f.read().split('\n')
		out = open(filename.split('.')[0] + '.rt', 'w')
		out.write(file_format_info)
		v = 0
		vn = 0
		faces = 0
		for line in f:
			if line.split(' ')[0] == 'f':
				faces += 1
			if line.split(' ')[0] == 'v':
				v += 1
			if line.split(' ')[0] == 'vn':
				vn += 1
		out.write("c %d %d %d\n" % (v, vn, faces))
		for line in f:
			if (line and (line[0] == 'v' or line[0] == 'f') and line[1] != 't'):
				if line[0] == 'f':
					nums = line[2:].replace('//', '/').replace('/', ' ').split(' ')
					if len(nums) > 6:
						out.write('f ' + ' '.join(nums[::3]) + ' ' + nums[2] + '\n')
					else:
						out.write('f ' + ' '.join(nums[::2]) + ' ' + nums[1] + '\n')
				else:
					out.write(line + '\n')
	except Exception as e:
		print e

if __name__ == '__main__':
	if len(sys.argv) > 1:
		for x in range(1, len(sys.argv)):
			to_rt(sys.argv[x])
	else:
		print "Usage: " + sys.argv[0], "[.obj file 1] [...]"
