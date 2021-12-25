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
	fmt.Println(lookup)

	err = reader.Err()
	if err != nil {
		panic(err)
	}

	root := ParseTemplate(template)
	root.Print()

	for i := 0; i < 5; i++ {
		root.ApplyTransform(lookup)
		root.Print()
	}
	counts := root.CnarCounts()
	var values []int
	for _, v := range counts {
		values = append(values, v)
	}
	sort.Ints(values)
	fmt.Printf("Most common %d, least common %d, sub %d\n",
		values[len(values)-1], values[0], values[len(values)-1]-values[0])
	// 4326 too low
}
