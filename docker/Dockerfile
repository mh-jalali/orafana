FROM oraclelinux:8

LABEL Description="Orafana on Docker" \
      Maintainer="Mohammad Hosein Jalali <mh.jalali@faash.ir>" \
      version="1.0" \
      build_date="2022-Apr-12"

USER root

ARG OGG_SOFTWARE
ARG OGG_TRAIL
ARG OGG_RPT
ARG OGG_PRM
ARG TNSNAMES_FILE


ENV ORA_INVENTORY=/home/oracle/oraInventory \
	ORACLE_HOME=/opt/ \
	OGG_HOME=/home/oracle/ogg \
	TNS_ADMIN=${ORACLE_HOME}/network/admin \
	LD_LIBRARY_PATH=/usr/lib/jvm/jre/lib/amd64/server:${LD_LIBRARY_PATH} 

ADD ${OGG_SOFTWARE} /home/oracle
ADD tnsnames.ora $TNS_ADMIN
COPY runOracleGoldenGate.sh /


RUN if [[-z "${OGG_SOFTWARE}" || -z "${OGG_TRAIL}" || -z "${OGG_RPT}" || -z "${OGG_PRM}" || -z "${TNSNAMES_FILE}"]]; then \
		echo "----------------------------------------------------------------------------------" && \
		echo "-- Missing build argument for Dockerfile. See README.md for usage instructions. --" && \
		echo "----------------------------------------------------------------------------------" && \
		exit 1; \
	fi; \
	dnf -y update && dnf -y upgrade \
	dnf -y install unzip python3-pip python39 python3.9-devel java-1.8.0-openjdk-headless oracle-database-preinstall-19c oracle-instantclient19-basic \
	pip3 install flask \
	mkdir -p ${OGG_HOME} && chmod 775 ${OGG_HOME} && chown oracle:oinstall ${OGG_HOME} \
	mkdir -p ${ORA_INVENTORY} && chmod 775 ${ORA_INVENTORY} && chown oracle:oinstall ${ORA_INVENTORY}
	


VOLUME [ "${OGG_RPT}" ]
VOLUME [ "${OGG_TRAIL}" ]
VOLUME [ "${OGG_PRM}" ]
WORKDIR  "${OGG_HOME}"
ENTRYPOINT [ "./runOracleGoldenGate.sh" ]


