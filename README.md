# Food Delivery App in C


## Done by-
- Aaftab Ahmed Khan 3122 23 5001 001
- Akash M 3122 23 5001 009
- Aniket Mondal 3122 23 5001 016

## Modules Required
1. Cjson (To store data and work with JSON files)
2. curl (For working with APIs)
3. gtk4 (For GUI)

## Other requirements (recommended)
1. WSL (Windows Subsystem for Linux)
2. Hardware Acceleration turned off
3. Git
4. VS Code

## How to set up your environment
### Obtaining Source Code
You can go to the [github repository](https://www.github.com/flashgrey3000/food-delivery-in-c)<br>
<img src="./images/i1.png" width=800><br>
And click on download zip folder or copy the web url and come to your git bash terminal and enter<br>
> `git clone https://github.com/FlashGrey3000/food-delivery-in-c.git`

You can now (after unzipping) go into the main code directory and open a WSL terminal on VS Code and perform the following steps to install the dependencies of our codebase.

---

### Installing cJson
cJSON is a ultralightweight json parse. This package contains the header files of cJSON.

To install cJSON  
`sudo apt install libcjson-dev`

### Installing cURL
libcurl is an easy-to-use client-side URL transfer library, supporting DICT,
FILE, FTP, FTPS, GOPHER, HTTP, HTTPS, IMAP, IMAPS, LDAP, LDAPS, POP3, POP3S,
RTMP, RTSP, SCP, SFTP, SMTP, SMTPS, TELNET and TFTP.
libcurl supports SSL certificates, HTTP POST, HTTP PUT, FTP uploading, HTTP
form based upload, proxies, cookies, user+password authentication (Basic,
Digest, NTLM, Negotiate, Kerberos), file transfer resume, http proxy tunneling
and more!  
libcurl is free, thread-safe, IPv6 compatible, feature rich, well supported,
fast, thoroughly documented and is already used by many known, big and
successful companies and numerous applications.
This package provides the development files (ie. includes, static library,
manual pages) that allow one to build software which uses libcurl.
SSL support is provided by OpenSSL.  

To install cURL  
`sudo apt install libcurl4-openssl-dev`

### Installing and configuring GTK4
This package contains development files for GTK4.  

To install GTK4  
`sudo apt install libgtk-4-dev` 

After installing we need to set `pkg-config` flags and libs. `pkg-config` helps compiling the gtk applications by locating the dependencies.  

 >`$ pkg-config --cflags gtk4
 -pthread -I/usr/include/gtk-4.0 -I/usr/lib64/gtk-4.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12`  

>`$ pkg-config --libs gtk4
 -pthread -lgtk-4 -lgdk-4 -lgio-2.0 -lpangoft2-1.0 -lgdk_pixbuf-2.0 -lpangocairo-1.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0
`

### Compiling
Now we can compile and run our application

``gcc `pkg-config --cflags gtk4` main.c -o main `pkg-config --libs gtk4` ``  

And run  
`./main`  

***If this causes a segmentation fault even before the windows are created then the issue might be that your system is trying to perform Hardware Acceleration on these gtk applications. This leads to memory leaks in the pango & gObject libraries.***

### Configuring
The following Environment variable prevents Hardware acceleration(Necessary only when your device is acting up)  
`export GSK_RENDERER=cairo`  


## Data Flow Diagrams

### Level 0
[Insert data flow diagrams]

### Level 1
[Insert data flow diagrams]

### Level 2
[Insert data flow diagrams]