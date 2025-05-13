// Измените палитру программы lissajous так, чтобы изображение было зелёного цвета
// на чёрном фоне, чтобы быть более похожим на экран осциллографа.
// Чтобы создать веб-цвет #RRGGBB, воспользуйтесь инструкцией color.RGBA{0xRR, 0xGG, 0xBB, 0xff},
// в которой каждая пара шестнадцатеричных цифр представляет яркость красного, зелёного и синего компонентов пикселя

package main

import (
	"image"
	"image/color"
	"image/gif"
	"io"
	"math"
	"math/rand"
	"os"
	"time"
)

var palette1 = []color.Color{color.Black, color.RGBA{0, 0xff, 0, 0xff}}

const (
	blackIndex1 = 0     // Первый цвет палитры
	greenIndex  = 1     // Следующий цвет палитры
	cycles_     = 5     // Количество полных колебаний
	res_        = 0.001 // Угловое разрешение
	size_       = 100   // Канва изображения охватывает размер [size..+size]
	nframes_    = 64    // Количество кадров анимации
	delay_      = 8     // Задержка между кадрами (единица - 10мс)
)

func main() {
	lissajous_(os.Stdout)
}

func lissajous_(out io.Writer) {
	r := rand.New(rand.NewSource(time.Now().UTC().UnixNano()))
	freq := r.Float64() * 3.0 // Относительная частота колебаний y
	anim := gif.GIF{LoopCount: nframes_}
	phase := 0.0 // Разность фаз

	for i := 0; i < nframes_; i++ {
		rect := image.Rect(0, 0, 2*size_+1, 2*size_+1)
		img := image.NewPaletted(rect, palette)
		for t := 0.0; t < cycles_*2*math.Pi; t += res_ {
			x := math.Sin(t)
			y := math.Sin(t*freq + phase)
			img.SetColorIndex(size_+int(x*size_+0.5), size_+int(y*size_+0.5), greenIndex)
		}
		phase += 0.1
		anim.Delay = append(anim.Delay, delay_)
		anim.Image = append(anim.Image, img)
	}
	gif.EncodeAll(out, &anim)
}
