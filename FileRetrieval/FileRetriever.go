package main

import "net"
import "fmt"
import "os"
import "time"

const address = "xandii.net:1081"
var server *net.TCPConn


func connectToServer() bool {
	tcpAddress, err := net.ResolveTCPAddr("tcp", "xandii.net:1081")
	if err != nil {
	    return false
	}
	conn, err2 := net.DialTCP("tcp", nil, tcpAddress)
	if err2 != nil {
	 	return false
	}
	server = conn
	return true
}


func receiveData(id int) ([]byte, bool) {
	dataStream := bufio.NewReader(server)
	server.Write(id)
	fileName := string(dataStream.ReadBytes('\n'))
	fileSize := dataStream.ReadBytes('\n')
	out, err := os.Create(fileName)
	if err != nil {
        return nil, false
	}
	defer out.Close()
	return nil, true
}

func main() {
	a := int([]byte{0, 0, 0, 1})
	fmt.Println(a)
    if !connectToServer() {
	    fmt.Println("connection failed")
	}
	outfile, err := os.Create("filecreationtest.class")
	if err != nil {
	    fmt.Println("file creation failed")
	}
	data, success := receiveData()
	if !success {
	   fmt.Println("receive data failed")
	}
	_, err2 := outfile.Write(data)
	if err2 != nil {
	    fmt.Println("file write fail")
	}
	for {
		time.Sleep(time.Second)
	}
}