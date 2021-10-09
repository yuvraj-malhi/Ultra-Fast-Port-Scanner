## Description   
<span style="color: red;">     A traditional port scanner has a particular task: to scan ports. Most commonly these are TCP ports on a device or a website with an IP address. Port scanners are particularly useful for network engineers, security analysts and basically anyone who wants to play around with websitetes and computers. 
They work in the following way:
  1. You specify one or more URLs or IP addresses.
  2. These are scanned for open TCP ports (like DNS, HTTP, HTTPs etc.)
  3. You are returned these port numbers and the service running on them.
  
The drawback for famous tools like nmap is : 
  1. They are incredibly **slow**! They take around 2 minutes to scan a single IP.
  2. They can only scan **only one** IP/URL at a time, so you have to wait for the first scan to fnish and enter the commands for the second scan..... and so on.
  3. It is difficult to learn the **syntax** of using these commands, especially if you don't use them that often.
  4. Their implementation is **hidden**. :(  So you have no idea what is actually going on. 
  
This project was created keeping in mind the deficiencies of all the present port scanners in mind. Hence this new scanner is _fast, easy to use, and open sourced._


### Setup & Usage
Visit [GitHub repository](https://github.com/yuvraj-malhi/Ultra-Fast-Port-Scanner) for complete details
  

## Working
For those of you who are coders and network engineers, I have explained the working of the code below:
(Note that I will just give a brief description of the code implementation. For detailed implementaion, open and read through scanner.c)

### Step 1: Service-Port Reading - populate()
This function registers all the important TCP ports and their respective services from port numbers 1-1024.

### Step 2: Parse domains - domainparse()
In this step, the names of domains that you just entered in "webpages.txt" is read out of the whole URL, the relevant **domain name** is extracted.

### Step 3: DNS lookup - lookup_webpage() -> getaddrinfo()
After a website's domain name has been read, then it's IP addresses (IPv4 and IPv6) are fetched using DNS protocol.

### Step 4: DNS lookup - lookup_webpage() -> connect()
For each of the port read in Step 1:
> This function registers all the important TCP ports and their respective services from port numbers 1-1024.

A child process for each port is created using fork() which connects to a port number on the IP address received from Step 3. This results in two possible outcomes:
  1. If connect() fails or times out    -    The port is probably closed, hence ignored.
  2. If connect() succeeds              -    The port is surely open, hence displayed.
