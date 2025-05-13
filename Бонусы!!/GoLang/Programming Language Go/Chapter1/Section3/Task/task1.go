package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	files := os.Args[1:]
	if len(files) == 0 {
		counts := make(map[string]int)
		if hasDups(os.Stdin, counts) {
			fmt.Println("stdin")
		}
		return
	}

	for _, arg := range files {
		counts := make(map[string]int)
		f, err := os.Open(arg)
		if err != nil {
			fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
			continue
		}
		if hasDups(f, counts) {
			fmt.Println(arg)
		}
		f.Close()
	}
}

func hasDups(f *os.File, counts map[string]int) bool {
	input := bufio.NewScanner(f)
	for input.Scan() {
		line := input.Text()
		counts[line]++
		if counts[line] > 1 {
			return true
		}
	}
	return false
}
