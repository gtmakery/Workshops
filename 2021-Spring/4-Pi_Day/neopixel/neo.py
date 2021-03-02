import board
import neopixel

neo_pin = board.D18

neo_matrix_rows = 8
neo_matrix_cols = 8


with neopixel.NeoPixel(neo_pin, neo_matrix_rows * neo_matrix_cols, auto_write=False) as pixels:
  def setPixel(x,y,color):
    pixels[y*neo_matrix_cols + (x if y%2==0 else (neo_matrix_cols-x))] = color

  # The code below can be any animation code you want
  t = 0
  while t < 10000000:
    t+=1
  #  setPixels((t*51)%8,(t*13)%8, (t%255,(t*9)%255,(t*13)%255))
    pixels.fill((t%255,(t*9)%255,(t*13)%255))
    pixels.show()
