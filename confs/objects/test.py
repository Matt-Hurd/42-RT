import sys

file_format_info =\
'''\
#Simplified .obj file format
#v denotes a vertex, a vec3
#vn denotes a normal
#f denotes a face. Consists of 3 vertices, followed by the normal
'''

def to_rt(filename):
	v = 0
	vn = 0
	face = 0
	f = open(filename, 'r')
	f = f.read().split('\n')
	for line in f:
		if (line and (line[0] == 'v' or line[0] == 'f') and line[1] != 't'):
			if line[1] == 'n':
				tmp = line.split(' ')
				print 'ft_set_vec3(&model->normals[%d], %s, %s, %s);' % (vn, tmp[1], tmp[2], tmp[3])
				vn += 1
			elif line[0] == 'v':
				tmp = line.split(' ')
				print 'ft_set_vec3(&model->vertices[%d], %f, %f, %f);' % (v, float(tmp[1]) * 10, float(tmp[2]) * 10, float(tmp[3]) * 10)
				v += 1
			elif line[0] == 'f':
				nums = line[2::].replace('/', ' ').split(' ')
				print 'model->faces[%d][0] = %s;' % (face, nums[::3][0])
				print 'model->faces[%d][1] = %s;' % (face, nums[::3][1])
				print 'model->faces[%d][2] = %s;' % (face, nums[::3][2])
				print 'model->faces[%d][3] = %s;' % (face, nums[2])
				# print('f ' + ' '.join(nums[::2]) + ' ' + nums[1])
				face += 1

if __name__ == '__main__':
	if len(sys.argv) > 1:
		for x in range(1, len(sys.argv)):
			to_rt(sys.argv[x])
	else:
		print "Usage: " + sys.argv[0], "[.obj file 1] [...]"
