// Измени программу так, чтобы она генерировала изображения разных цветов
// добавляя в палитру больше значений, а затем выводя их путём изменения третьего аргумента
// функции SetColorIndex некоторым не тривиальным способом

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

var palette = []color.Color{
	color.White,
	color.Black,
	color.RGBA{0xFF, 0x00, 0x00, 0xFF}, // Красный
	color.RGBA{0x00, 0xFF, 0x00, 0xFF}, // Зелёный
	color.RGBA{0x00, 0x00, 0xFF, 0xFF}, // Синий
	color.RGBA{0xFF, 0xFF, 0x00, 0xFF}, // Жёлтый
	color.RGBA{0xFF, 0x00, 0xFF, 0xFF}, // Пурпурный
	color.RGBA{0x00, 0xFF, 0xFF, 0xFF}, // Голубой
}

const (
	whiteIndex = 0     // Первый цвет палитры
	blackIndex = 1     // Следующий цвет палитры
	cycles     = 5     // Количество полных колебаний
	res        = 0.001 // Угловое разрешение
	size       = 100   // Канва изображения охватывает размер [size..+size]
	nframes    = 64    // Количество кадров анимации
	delay      = 8     // Задержка между кадрами (единица - 10мс)
)

func main() {
	lissajous(os.Stdout)
}

func lissajous(out io.Writer) {
	r := rand.New(rand.NewSource(time.Now().UTC().UnixNano()))
	freq := r.Float64() * 3.0 // Относительная частота колебаний y
	anim := gif.GIF{LoopCount: nframes}
	phase := 0.0 // Разность фаз
	colors := []uint8{blackIndex, 2, 3, 4, 5, 6, 7}
	for i := 0; i < nframes; i++ {
		rect := image.Rect(0, 0, 2*size+1, 2*size+1)
		img := image.NewPaletted(rect, palette)
		randomIndex := colors[rand.Intn(len(colors))]
		for t := 0.0; t < cycles*2*math.Pi; t += res {
			x := math.Sin(t)
			y := math.Sin(t*freq + phase)
			img.SetColorIndex(size+int(x*size+0.5), size+int(y*size+0.5), randomIndex)
		}
		phase += 0.1
		anim.Delay = append(anim.Delay, delay)
		anim.Image = append(anim.Image, img)
	}
	gif.EncodeAll(out, &anim)
}
