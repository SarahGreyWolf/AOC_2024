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
	input, err := os.ReadFile(args[0])

	if err != nil {
		panic(err)
	}

	// text := string(bytes)
	result := part1(&input)
	fmt.Printf("The result of all mul instructions is %d\n", result)
	result = part2(&input)
	fmt.Printf("The result of all mul instructions abiding by do and don't is %d\n", result)

}

func part1(input *[]byte) int {
	exp, err := regexp.Compile(`mul\((\d*),(\d*)\)`)

	if err != nil {
		panic(err)
	}

	found := exp.FindAllSubmatch(*input, -1)

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

func part2(input *[]byte) int {
	exp, err := regexp.Compile(`(mul\((\d*),(\d*)\)|don't\(\)|do\(\))`)

	if err != nil {
		panic(err)
	}

	found := exp.FindAllSubmatch(*input, -1)

	if len(found) == 0 {
		panic("Found zero matching")
	}

	results := 0
	do := true
	for i := range len(found) {
		if string(found[i][1]) == "do()" {
			do = true
			continue
		} else if string(found[i][1]) == "don't()" {
			do = false
			continue
		}
		if !do {
			continue
		}
		lhs, _ := strconv.Atoi(string(found[i][2]))
		rhs, _ := strconv.Atoi(string(found[i][3]))
		results += lhs * rhs
	}

	return results
}
