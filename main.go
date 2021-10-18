package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	bufferSize := 1024 * 1024 * 1024 * 8
	iterations := 10
	accessCount := 10000000
	buffer := make([]byte, 1024*1024*1024*8)
	durations := make([]time.Duration, 0)
	rand.Seed(time.Now().UnixNano())

	for i := 0; i < iterations; i++ {
		start := time.Now()
		for j := 0; j < accessCount; j++ {
			buffer[rand.Intn(bufferSize)] = byte(rand.Intn(128))
		}
		duration := time.Since(start)
		durations = append(durations, duration)
	}

	total := time.Duration(0)
	for i := 0; i < len(durations); i++ {
		total = total + durations[i]
	}

	avg := int(total.Milliseconds()) / len(durations)
	fmt.Printf("Average latency in milliseconds: %v \n\n", avg)

	for i := 0; i < len(durations); i++ {
		fmt.Printf("Iteration #%v: %v\n", i, durations[i])
	}
}
