FROM oraclelinux:8
LABEL maintainer="Mohamad Hosein Jalali"
LABEL email="mh-jalali@faash.ir"
LABEL version="1.0"
LABEL description="Orafana Dockerfile"
LABEL build_date="2022-Apr-03"
RUN dnf update -y && dnf  upgrade -y
RUN dnf install unzip  python39  python39-devel  java-11-openjdk oracle-database-preinstall-19c -y
RUN mkdir -p /opt/ogg && chmod 775 /opt/ogg && chown oracle:oinstall /opt/ogg
RUN mkdir -p /opt/instance_client && chmod 775 /opt/instance_client && chown oracle:oinstall /opt/instance_client
RUN mkdir -p /opt/oraInventory && chmod 775 /opt/oraInventory && chown oracle:oinstall /opt/oraInventory
RUN mkdir -p /opt/tmp && chmod 775 /opt/tmp && chown oracle:oinstall /opt/tmp
USER oracle
##Enviroment Variables
ENV ORA_INVENTORY=/opt/oraInventory
ENV ORACLE_HOME=/opt/instance_client
ENV ORACLE_SID=shatoot
ENV OGG_HOME=/opt/ogg
ENV TNS_ADMIN=$ORACLE_HOME/network/admin
ENV PYTHONHOME=$OGG_HOME/dirprm
ENV JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64/lib/server
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$JAVA_HOME
##Copy Software
COPY 191004_fbo_ggs_Linux_x64_shiphome.zip /opt/tmp
COPY instantclient-basiclite-linux.x64-21.1.0.0.0.zip /opt/tmp
##Unzip
RUN cd /opt/tmp && unzip 191004_fbo_ggs_Linux_x64_shiphome.zip
RUN unzip -d $ORACLE_HOME /opt/tmp/instantclient-basiclite-linux.x64-21.1.0.0.0.zip
##Create Goldengate Subdirs
COPY tnsnames.ora $TNS_ADMIN
WORKDIR /opt/tmp/fbo_ggs_Linux_x64_shiphome/Disk1
RUN ./runInstaller -silent -showProgress -waitForCompletion \
		 INSTALL_OPTION=ORA19c \
		 SOFTWARE_LOCATION=${OGG_HOME} \
		 START_MANAGER=FALSE \
		 MANAGER_PORT=7809 \
		 DATABASE_LOCATION=${ORACLE_HOME} \
		 INVENTORY_LOCATION=${ORA_INVENTORY} \
		 UNIX_GROUP_NAME=oinstall 
RUN mkdir -p $OGG_HOME/
RUN mkdir -p $OGG_HOME/dirprm
RUN mkdir -p $OGG_HOME/dirdat
RUN mkdir -p $OGG_HOME/dirchk
RUN mkdir -p $OGG_HOME/dirrpt
USER root
RUN $ORA_INVENTORY/orainstRoot.sh
USER oracle
WORKDIR $OGG_HOME
CMD ["ggsci","CREATE SUBDIRS"]
#CMD ["ggsci","ADD CREDENTIALSTORE"]
#CMD ["ggsci","ALTER CREDENTIALSTORE ADD USER C##OGGADMIN@SHATOOT ALIAS OGGADMIN"]
#TODO: after above command ggsci wait for password
CMD ["ggsci","DBLOGIN USERIDALIAS OGGADMIN"]
CMD ["ggsci","REGISTER EXTRACT EORA DATABASE CONTAINER (SHATOOTPDB)"]
CMD ["ggsci","ADD EXTRACT EORA , TRANLOG INTEGRATED , BEGIN NOW"]
CMD ["ggsci","ADD EXTTRAIL ./didat/e1 EXTRACT EORA"]
##CMD ["ggsci","START EORA"]
#Cleanup
RUN rm -rf /opt/tmp
