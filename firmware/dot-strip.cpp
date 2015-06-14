/*-------------------------------------------------------------------------
  SparkStrip is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  SparkStrip is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with SparkStrip.  If not, see
  <http://www.gnu.org/licenses/>.

  The original version of SparkStrip is available at:
      https://github.com/DonGar/spark-strip
  -------------------------------------------------------------------------*/

#include "dot-strip.h"

DotStrip::DotStrip(int pixelCount) :
ColorStrip(pixelCount) {

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  drawSolid(BLACK);
}

void DotStrip::drawPixel(Color color) {
  if (this->drawOffset == 0) {
    // Signal the start of draw.
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
  }

  ColorStrip::drawPixel(color);

  SPI.transfer(0xFF);
  SPI.transfer(color.green);
  SPI.transfer(color.blue);
  SPI.transfer(color.red);
}

void DotStrip::finishDraw() {
  ColorStrip::finishDraw();

  // Signal the end of draw.
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
}
