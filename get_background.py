
# ffmpeg -i niceout.mp4 pictures/output_%04d.png
from PIL import Image
from os import listdir
from collections import Counter, defaultdict
d = defaultdict(lambda: defaultdict(list))
#d = Counter()

def f():
	for filename in listdir('.')[:300]:
		im = Image.open(filename)
		pixels = list(im.getdata())
		width, height = im.size
		for x in range(width):
			for y in range(height):
				pixel = pixels[y*width+x]	
				d[x][y].append(pixel)

	im = Image.new("RGB", (width, height), "black")
	pixels = im.load()
	for a in d.items():
		for b in a[1].items():
			x = a[0]
			y = b[0]
			ll = b[1]	
			pixels[x,y] = Counter(ll).most_common()[0][0]
	im.save("e.png")

if __name__ == "__main__":
	f()
