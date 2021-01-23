# Ultra-Fast Port Scanner
## Introduction
A traditional port scanner has a particular task: to scan ports. Most commonly these are TCP ports on a device or a website with an IP address. Port scanners are particularly useful for network engineers, security analysts and basically anyone who wants to play around with websitetes and computers. 
They work in the following way:
  1. You specify one or more URLs or IP addresses.
  2. These are scanned for open TCP ports (like DNS, HTTP, HTTPs etc.)
  3. You are returned these port numbers and the service running on them.
  
The drawback for famous tools like nmap is : 
  1. They are incredibly slow! They take around 2 minutes to scan a single IP.
  2. They can only scan one IP/URL at a time, so you have to wait for the first scan to fnish and enter the commands for the second scan..... and so on.
  3. It is difficult to learn the syntax of using these commands, especially if you don't use them that often.
  4. Their implementation is hidden. :(  So you have no idea what is actually going on. 
  
This project was created keeping in mind the deficiencies of all the present port scanners in mind. Hence this new scanner is fast, easy to use, and open sourced.
