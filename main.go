package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	SizeGb = 1024 * 1024 * 1024
	SizeMb = 1024 * 1024
	SizeKb = 1024
)

func main() {
	fmt.Printf("%d, %v\n", 1, randRead(SizeKb*1))
	fmt.Printf("%d, %v\n", 2, randRead(SizeKb*2))
	fmt.Printf("%d, %v\n", 4, randRead(SizeKb*4))
	fmt.Printf("%d, %v\n", 8, randRead(SizeKb*8))
	fmt.Printf("%d, %v\n", 16, randRead(SizeKb*16))
	fmt.Printf("%d, %v\n", 32, randRead(SizeKb*32))
	fmt.Printf("%d, %v\n", 64, randRead(SizeKb*64))
	fmt.Printf("%d, %v\n", 128, randRead(SizeKb*128))
	fmt.Printf("%d, %v\n", 256, randRead(SizeKb*256))
	fmt.Printf("%d, %v\n", 2000, randRead(SizeMb*2))
	fmt.Printf("%d, %v\n", 4000, randRead(SizeMb*4))
	fmt.Printf("%d, %v\n", 8000, randRead(SizeMb*8))
	fmt.Printf("%d, %v\n", 16000, randRead(SizeMb*16))
	fmt.Printf("%d, %v\n", 32000, randRead(SizeMb*32))
	fmt.Printf("%d, %v\n", 64000, randRead(SizeMb*64))
	fmt.Printf("%d, %v\n", 128000, randRead(SizeMb*128))
	fmt.Printf("%d, %v\n", 256000, randRead(SizeMb*256))
	fmt.Printf("%d, %v\n", 512000, randRead(SizeMb*512))
	fmt.Printf("%d, %v\n", 1000000, randRead(SizeGb*1))
	fmt.Printf("%d, %v\n", 2000000, randRead(SizeGb*2))
}

func randRead(bufferSize int) float64 {
	iterations := 15
	accessCount := 10 * 1000 * 1000
	buffer := make([]byte, bufferSize)
	durations := make([]time.Duration, 0)
	rand.Seed(time.Now().UnixNano())

	for i := 0; i < bufferSize; i++ {
		buffer[i] = 0
	}

	for i := 0; i < iterations; i++ {
		start := time.Now()
		for j := 0; j < accessCount; j++ {
			buffer[rand.Intn(bufferSize)] = byte(72)
		}
		duration := time.Since(start)
		durations = append(durations, duration)
	}

	total := time.Duration(0)
	for i := 0; i < len(durations); i++ {
		total = total + durations[i]
	}

	avg := float64(total.Milliseconds()) / float64(len(durations))
	return avg
}
