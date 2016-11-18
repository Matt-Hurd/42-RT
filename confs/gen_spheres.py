from random import random
import sys

num_spheres = 100
size = 10
xrang = 1000
yrang = 1600
ymin = -1000
height_diff = 10
print('''[scene]
	name=RT
	width=1200
	height=800
	camera=-30.0, -60.0, -200.0
	cameraRot=0.0, 0.0, 0.0
	fov=90
	aa=0
	depth=3

[light]
	radiance=100
	pos=0.0, -400.0, -400.0
	color=255, 255, 255

[light]
	radiance=100
	pos=0.0, -180.0, -400.0
	color=255, 255, 255

[plane]
	pos=0.0, 10.0, 0.0
	rot=90.0, 0.0, 0.0
	color=142, 124, 105

[plane]
	pos=0.0, -500.0, 0.0
	rot=90.0, 0.0, 0.0
	color=47, 191, 226

[sphere]
	radius=60
	pos=0.0, -60.0, 0.0
	rot=0.0, 0.0, 0.0
	color=0, 0, 0
	reflect=80
	gloss=70

[sphere]
	radius=60
	pos=-90.0, -60.0, 90.0
	rot=0.0, 0.0, 0.0
	color=0, 0, 0
	transparency=50
	density=250''')
normal = 0
trans = 0
reflect = 0
for s in range(num_spheres):
	x = (random() - 0.5) * xrang
	y = random() * yrang + ymin
	z = -random() * height_diff
	r = random() * 255
	g = random() * 255
	b = random() * 255
	t = random()
	print("[sphere]")
	print("	radius=%d" % size)
	print("	pos=%f, %f, %f" % (x, z, y))
	print("	color=%d, %d, %d" % (r, g, b))
	if (t < 0.1):
		trans += 1
		print("	transparency=%d" % (random()*100))
		print("	density=250")
	elif t > 0.9:
		reflect += 1
		print("	reflect=80")
		print("	gloss=70")
	else:
		normal += 1
	print ("")
sys.stderr.write("Normal: %d\nTranslucent: %d\nReflective: %d\n" %(normal, trans, reflect))
