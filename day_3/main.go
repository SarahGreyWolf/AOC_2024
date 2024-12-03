package main

import (
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func main() {
	args := os.Args[1:]
	if len(args) != 1 {
		fmt.Println("Usage: go run main.go <path_to_file.txt>")
	}
	bytes, err := os.ReadFile(args[0])

	if err != nil {
		panic(err)
	}

	// text := string(bytes)
	result := part1(&bytes)
	fmt.Printf("The result of all mul instructions is %d\n", result)

}

func part1(bytes *[]byte) int {
	exp, err := regexp.Compile(`mul\((\d*),(\d*)\)`)

	if err != nil {
		panic(err)
	}

	found := exp.FindAllSubmatch(*bytes, -1)

	if len(found) == 0 {
		panic("Found zero matching")
	}

	results := 0
	for i := range len(found) {
		lhs, _ := strconv.Atoi(string(found[i][1]))
		rhs, _ := strconv.Atoi(string(found[i][2]))
		results += lhs * rhs
	}

	return results
}

}
