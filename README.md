in order to config the cloud follow these steps 

create the corresponding VMs using Ubuntu images.
On each vm run the following commands
to create ssh key
  ssh-keygen -t rsa -b 4096
  cat ~/.ssh/id_rsa.pub
copy the shown key into all the other VMs 
  click on VM name 
  go to edit
  add ssh key
NOTE: it is sufficient to add the master node key to all others and all others only to master node

now test the ssh connection using 
  ssh user@ip 
  then install openMPI on all of them using 
    sudo apt update
    sudo apt install openmpi-bin openmpi-common libopenmpi-dev
    mpirun --version
afterwards on the master node compile your code 
mpic++ -o compiled_file_name your_cpp_code.cpp

then you should run the distribute.sh from scripts to copy the compiled code to all other VMs

bellow we have list of usfull command you may need
chmod +x file_name to make the file executable
./filename to run the file

REMEMBER TO STOP THE VMS AFTER YOU'RE DONE

