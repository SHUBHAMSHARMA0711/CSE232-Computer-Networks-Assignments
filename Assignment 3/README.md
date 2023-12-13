# Setup Instructions

## VM Setup

- You can use a Hypervisor of your choice but we      recommend Oracle's **Virtual Box** if its available for your platform (*At the time of this writing, Virtual Box does not have a stable build for Apple Silicon - M1/M2 Macs*)

- The steps given below are for Virtual Box but can be easily adapted for other Hypervisors as well. Please refer to the documentation of your Hypervisor for detailed information on setting up a VM.

- Go to https://www.virtualbox.org/wiki/Linux_Downloads to download virtual box for your platform (x86 - windows, linux, mac).

- You will require two VM's - One for running the client and one for running the server (Both the VM's should be able to communicate with each other)

- Client Specs
    - Memory  : 2048MB
    - Disk    : 10GB- 15GB (For Guest OS)
    - CPU     : 2cores
    - OS      : Ubuntu 22.04 + / Debian 11+ (GLIBC VERSION - 2.31+)

- Server Specs
    - Memory  : 2048MB
    - Disk    : 10GB - 15GB (For Guest OS)
    - CPU     : 3cores
    - OS      : Any version of ubuntu/debian

- For M1/M2 based Macs, you can use Ubuntu for Arm (https://ubuntu.com/download/server/arm)

- Go to File->Preferences->Network in virtual box 
- Click on network and create a new nat network
    - Specify a name for the network (eg. cn-lab)
    - Specify an ip range in CIDR notation (eg. 10.0.2.0/24)
    - Set Supports DHCP to true
- Now for both the server and client vm's go to the VM settings and under Network set the **Attached To** field to **NAT Network** and *Network Name* to the name previously assigned *(cn-lab)*
- Now proceed to install the OS on the VM's. 

- Portforwarding (Optional) : 
    - Note the ip of both the client and server. Now go to File->Preferences->Network and double click on cn-lab. 
    - Click on Portforwarding and set the guest ip's for client and server along with ssh port number (22). In the Host Port set a unique port number for Server and Client. 

    - Click on Ok and run the VM's.

    - Now from Host machine open a terminal and run ssh -p <host_port> to connect to the client or server and communicate via ssh

## Server and Client Settings 

- Start Client and Server VM's and run `ulimit -n 8192` to increase the max number of files that can be opened by a process at a time.

## Client Usage

- The client is provided to you as a part of this assignment for testing. 
- untar the clients.xz file by running the command `tar -xvf clients.xz`
- Copy the client binary to your *Client VM* as per the target architecture 

- When testing, run the client binary inside the Client VM as follows 
    - For x86_64   : `./client_x86_64 <ip:port> <num_requests> <num_concurrent_connections>` 
    - For Aarch 64 : `./client_aarch64 <ip:port> <num_requests> <num_concurrent_connections>` 

- ip:port - Ip and port of the server (Eg. 10.0.2.5:8081)
- num_request - Total number of requests to send per connection.
- num_concurrent_connections - Total number of concurrent connections to be maintained between client and server

- Please note that the output of client may not appear in sorted order. But if your server was able to service all the requests of the client, the client will end successfully. If you wish to check the output then redirect the output of client to a file and use system utilities to figure out the highest number of connection in the output.

## Additional Tips when writing the server

- If you are getting a Signal 13 error when running the server, you can ignore that signal by adding `signal(SIGPIPE, SIG_IGN);` at the beginning of main. If there are any actual read/write errors, they will still be reported.


## FAQ

- Finding peak memory utilization of a process :
    - Get time package `sudo apt install time`
    - Run time command with the correct path */usr/bin/time -v <process>* and observe the output
    - The value next to *Maximum resident size* indicates the peak memory usage of the process

- Using htop
    - https://support.cloudways.com/en/articles/5120765-how-to-monitor-system-processes-using-htop-command
    - https://www.geeksforgeeks.org/using-htop-to-monitor-system-processes-on-linux/
    



 