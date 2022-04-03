# orafana
Custom Oracle Goldengate UserExit (C-Python)


--Tip
1.In order to avoid generating trail files ,
after processing each record in EXIT_CALL_PROCESS_RECORD ,
set the value for *exit_call_result to EXIT_IGNORE_VAL.

2.In order to import orafana.py module in CUSEREXIT (PyImport_ImportModule)
add SETENV (PYTHONHOME="Path to orafana.py module") in extract parameter file ,
otherwise starting extract process will fail with "OGG-01122  undefined symbol".




--Docker
sudo docker login
sudo docker pull oraclelinux:8


cd $Project_Path/docker
sudo docker build --no-cache -t orafana:v1 .



--Docker Build With Proxy Settings
sudo docker build --build-arg https_proxy=https://172.16.15.53:913 --no-cache -t orafana:v1 .

