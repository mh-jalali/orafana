FROM oraclelinux:8
RUN dnf install unzip , python39 , python39-devel , java-11-openjdk
COPY 191004_fbo_ggs_Linux_x64_shiphome.zip /opt
COPY instantclient-basic-linux.x64-21.5.0.0.0dbru.zip /opt
RUN cd /opt && unzip 191004_fbo_ggs_Linux_x64_shiphome.zip && rm -rf 191004_fbo_ggs_Linux_x64_shiphome.zip
RUN cd /opt && unzip instantclient-basic-linux.x64-21.5.0.0.0dbru.zip && rm -rf instantclient-basic-linux.x64-21.5.0.0.0dbru.zip
ENV ORA_INVENTORY=/opt/oraInventory
ENV ORACLE_HOME=/opt/instantclient_21_5
ENV ORACLE_SID=shatoot
ENV OGG_HOME=/opt/ogg
ENV TNS_ADMIN=/opt/instantclient_21_5/network/admin
ENV PYTHONHOME=$OGG_HOME/dirprm
ENV JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64/lib/server
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$JAVA_HOME
##Goldengate Subdirs
RUN mkdir -p $OGG_HOME/
RUN mkdir -p $OGG_HOME/dirprm
RUN mkdir -p $OGG_HOME/dirdat
RUN mkdir -p $OGG_HOME/dirchk
RUN mkdir -p $OGG_HOME/dirrpt
##Volum For OGG
VOLUME 
VOLUME 
VOLUME 
VOLUME 
COPY tnsnames.ora $TNS_ADMIN
WORKDIR /opt/fbo_ggs_Linux_x64_shiphome/Disk1
RUN ./runInstaller -silent -showProgress -waitforcompletion -responseFile #Path to responsefile
WORKDIR $OGG_HOME
CMD ["ggsci","CREATE SUBDIRS"]
CMD ["ggsci","ADD CREDENTIALSTORE"]
CMD ["ggsci","ALTER CREDENTIALSTORE ADD USER C##OGGADMIN@SHATOOT ALIAS OGGADMIN"]
#TODO: after above command ggsci wait for password
CMD ["ggsci","DBLOGIN USERIDALIAS OGGADMIN"]
CMD ["ggsci","REGISTER EXTRACT EORA DATABASE CONTAINER (SHATOOTPDB)"]
CMD ["ggsci","ADD EXTRACT EORA , TRANLOG INTEGRATED , BEGIN NOW"]
CMD ["ggsci","ADD EXTTRAIL ./didat/e1 EXTRACT EORA"]
##CMD ["ggsci","START EORA"]






 
