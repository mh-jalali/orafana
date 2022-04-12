#!/bin/bash

function createSubdirs {
    echo "CREATE SUBDIRS" | ${runAsUser} ${OGG_HOME}/ggsci
}

function startManager {
    echo "START MGR" | ${runAsUser} ${OGG_HOME}/ggsci
}

function isOGGRunning {

}



function startCapture {
    echo "START EXTRACT EORA" | ${runAsUser} ${OGG_HOME}/ggsci
}

function alterCapture {
    echo "ALTER EXTRACT EORA , SCN ${SCN_NO}" | ${runAsUser} ${OGG_HOME}/ggsci
}

function checkRegister {

}

function registerCapture {
    loginOGG;
    echo "REGISTER EXTRACT EORA DATABASE CONTAINER (SHATOOTPDB)" | ${runAsUser} ${OGG_HOME}/ggsci
}

function unregisterCapture {
    loginOGG;
    echo "UNREGISTER EXTRACT EORA DATABASE" | ${runAsUser} ${OGG_HOME}/ggsci
}

function loginOGG {
    echo "DBLOGIN USERIDALIAS OGGADMIN" | ${runAsUser} ${OGG_HOME}/ggsci
}

function createCredentialStore {
    echo "CREATE CREDENTIALSTORE" | ${runAsUser} ${OGG_HOME}/ggsci
    echo "ALTER CREDENTIALSOTRE ADD USER OGGADMIN@SHATOOTPDB" | ${runAsUser} ${OGG_HOME}/ggsci
    #PASSWORD PROMPT
}

function createCapture {
    if [!checkRegister]; then
        loginOGG;
        registerCapture;
        if [!hasCheckpoint]; then
            echo "ADD EXTRACT EORA , TRANLOG INTEGRATED , BEGIN NOW" | ${runAsUser} ${OGG_HOME}/ggsci
            echo "ADD EXTTRAIL ./dirdat/e1 , EXTRACT EORA , MEGABYTES 500" | ${runAsUser} ${OGG_HOME}/ggsci
        else
            readCheckpoint;
            echo "ADD EXTRACT EORA , TRANLOG INTEGRATED" | ${runAsUser} ${OGG_HOME}/ggsci
            alterCapture(${SCN_NO});
        fi
    else
        loginOGG;
        echo "ADD EXTRACT EORA , TRANLOG INTEGRATED , BEGIN NOW" | ${runAsUser} ${OGG_HOME}/ggsci
        echo "ADD EXTTRAIL ./dirdat/e1 , EXTRACT EORA , MEGABYTES 500" | ${runAsUser} ${OGG_HOME}/ggsci
    fi
}

function hasCheckpoint {

}

function readCheckpoint {

}

function installOGG {
    ${runAsUser} ./runInstaller -silent -showProgress -waitForCompletion \
                    INSTALL_OPTION=ORA19c \
                    SOFTWARE_LOCATION=${OGG_HOME} \
                    START_MANAGER=FALSE \
                    MANAGER_PORT=7809 \
                    DATABASE_LOCATION=${ORACLE_HOME} \
                    INVENTORY_LOCATION=${ORA_INVENTORY} \
                    UNIX_GROUP_NAME=oinstall 2>/dev/null
}


function getVersion {

}

USER oracle
##Copy Software

##Unzip
RUN cd /opt/tmp && unzip 191004_fbo_ggs_Linux_x64_shiphome.zip
RUN unzip -d $ORACLE_HOME /opt/tmp/instantclient-basiclite-linux.x64-21.1.0.0.0.zip
##Create Goldengate Subdirs

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
