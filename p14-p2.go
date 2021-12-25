package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

type Node struct {
	next *Node
	char byte
}

func ParseTemplate(template string) *Node {
	root := Node{nil, template[0]}
	current := &root
	for i := 1; i < len(template); i++ {
		next := &Node{nil, template[i]}
		current.next = next
		current = next
	}
	return &root
}

func (root Node) Print() {
	node := &root
	for node != nil {
		fmt.Print(string(node.char))
		node = node.next
	}
	fmt.Println()
}

func (root *Node) ApplyTransform(lookup map[string]byte) {
	last := root
	current := root.next

	for current != nil {
		chars := string([]byte{last.char, current.char})
		c, ok := lookup[chars]
		if ok {
			inserted := &Node{current, c}
			last.next = inserted
		}

		last = current
		current = current.next
	}
}

func (root *Node) CnarCounts() map[byte]int {
	counts := make(map[byte]int)
	current := root
	for current != nil {
		counts[current.char]++
		current = current.next
	}
	return counts
}

func main() {
	file, err := os.Open("p14.txt")
	defer file.Close()

	if err != nil {
		panic(err)
	}
	reader := bufio.NewScanner(file)
	reader.Scan()
	template := reader.Text()
	fmt.Println(template)

	// skip empty line
	reader.Scan()
	reader.Text()

	lookup := make(map[string]byte)

	for reader.Scan() {
		line := reader.Text()
		parts := strings.Split(line, " -> ")
		lookup[parts[0]] = parts[1][0]
	}

	err = reader.Err()
	if err != nil {
		panic(err)
	}

	counts := make(map[string]int64)
	for i := 0; i < len(template)-1; i++ {
		part := template[i : i+2]
		counts[part]++
	}
	fmt.Println(counts)

	var countsByChar map[byte]int64
	for iter := 0; iter < 40; iter++ {
		newCounts := make(map[string]int64)
		countsByChar = make(map[byte]int64)
		countsByChar[template[len(template) - 1]] = 1

		for part, count := range counts {
			inserted := lookup[part]

			part1 := string([]byte{part[0], inserted})
			part2 := string([]byte{inserted, part[1]})
			newCounts[part1] += count
			newCounts[part2] += count
			countsByChar[part[0]] += count
			// countsByChar[part[1]] += count
			countsByChar[inserted] += count
		}
		counts = newCounts
	}
	fmt.Println(countsByChar)

	var values []int64
	for _, v := range countsByChar {
		values = append(values, v)
	}
	sort.Slice(values, func(i, j int) bool { return values[i] < values[j] })
	fmt.Printf("Most common %d, least common %d, sub %d\n",
		values[len(values)-1], values[0], values[len(values)-1]-values[0])
	// 9409635290165 too high
	// 7057212716818 too high
	// 4704817645082 too low
	// 4704817645083
}
