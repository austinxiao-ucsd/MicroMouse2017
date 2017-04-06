import pygame

x = y = 0
running = 1
bgcolor = 0, 0, 0
fgcolor = 255, 255, 255
linecolor = bgcolor
LEFT = 1

cell_width = 1
cell_height = 1


f = open( "input.dat", "w")
cell_height = 1
startpos = endpos = (0,0)

fieldsize = (160, 360)  # american football field is 360 feet long x 160 feet across
windowsize = (400, 600)
scalefactor = windowsize[0]/fieldsize[0], windowsize[1]/fieldsize[1];

screen = pygame.display.set_mode((windowsize))
screen.fill(bgcolor)

pygame.init()
# initialize font; must be called after 'pygame.init()' to avoid 'Font not Initialized' error
myfont = pygame.font.SysFont("monospace", 30)

# render text
label = myfont.render("Sensor Simulator", 1, (255,255,0))
screen.blit(label, (50, 20))

def texts(s, size, pos):
	 #if self.fonts.get(size) is None: self.fonts[size] = pygame.font.SysFont(None, size)
	 font=pygame.font.Font(None,30)
	 rendertext=font.render(s, 1,(255,255,255))
	 screen.blit(rendertext, pos)

texts("Path:", 30, (50,70))
pygame.display.flip()



while running:
	event = pygame.event.poll()
	if event.type == pygame.QUIT:
		running = 0
	elif event.type == pygame.MOUSEBUTTONDOWN and event.button == LEFT:
		linecolor = fgcolor
		startpos = endpos = event.pos
		texts( str(cell_height),10,startpos)
	elif event.type == pygame.MOUSEBUTTONUP and event.button == LEFT:
		linecolor = bgcolor
		endpos = event.pos
		texts( str(cell_height),10,endpos)
	elif event.type == pygame.MOUSEMOTION:
		if linecolor == fgcolor:
			x, y = endpos = event.pos
			
			print x, y
			s = str( cell_width) + ','+ str( cell_height) + ',' + str(x) + ',' + str(y) + '\n'
			f.write(s)
		
			pygame.draw.line( screen, linecolor, startpos, endpos )
			pygame.display.flip()
			startpos = endpos
	elif event.type == pygame.KEYDOWN:
		key = event.key
		if key >= pygame.K_0 and key <= pygame.K_9:
			cell_height = key - pygame.K_0
			texts("cell_height:" + str(cell_height), 30, (50,70))
			pygame.display.flip()	


f.close()



