# Ultra-Fast Port Scanner
## Introduction
A traditional port scanner has a particular task: to scan ports. Most commonly these are TCP ports on a device or a website with an IP address. Port scanners are particularly useful for network engineers, security analysts and basically anyone who wants to play around with websitetes and computers. 
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

## Usage
### Step I
Download "scanner.c" and move to the folder where you have downloaded it Command Line Interface.
![image](https://user-images.githubusercontent.com/76866159/105578937-a12eff00-5da9-11eb-99f1-fa3c0e05d8b4.png)


## Step II
Make a new file "webpages.txt" and enter enter the website URLs you want to scan line-by-line using vi-editor. 
![image](https://user-images.githubusercontent.com/76866159/105579035-eeab6c00-5da9-11eb-8dd4-9c1ee1f96467.png)
In my case, I have entered the URL for Google and Yahoo.


## Step III
Run the command gcc scanner.c
![image](https://user-images.githubusercontent.com/76866159/105579123-83ae6500-5daa-11eb-84f4-1f1af7410e82.png)
If successful, then a file "a.out" will be created.

## Step IV
Run the command ./a.out
Give ~30 seconds for the program to run.
![image](https://user-images.githubusercontent.com/76866159/105579230-3a124a00-5dab-11eb-97f1-19962f91fa74.png)

Complete! 
Now you can see the results which are **5X** faster than nmap and also very easy to understand.
For each website the program shows a list of:
  1. IPv4 addresses
  2. IPv6 addresses
  3. Ports open on the IPv4 addresses
  4. Ports open on the IPv6 addresses
  5. Services running on each of the above open ports.
  
  
  


