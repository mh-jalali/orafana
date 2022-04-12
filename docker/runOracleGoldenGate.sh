#!/bin/bash

function getCommand {
    local primary=$1; shift
    local alternate=$*
    for check in ${alternate} ${primary}; do
        command=$(command -v ${check} 2>/dev/null) && break
    done
    [[ -z "${command}" ]] && {
        [[ ! -z "${alternate}" ]] && echo "Error: Cannot locate command ${primary} or ${alternate}" \
                                  || echo "Error: Cannot locate command ${primary}"
        exit 1
    }
    eval "${primary^^}=${command}"
}

getCommand runuser
runAsUser="${RUNUSER} -u oracle --"
OGGProcesses="(extract|ggsci|mgr)"

function tailReport {
    getCommand tail
    local rptFile="$1"
    while [[ ! -f  "${rptFile}" ]]; do
        sleep 1
    done
    ${TAIL} --lines=+1 -F ${rptFile}
}

function setExecutable {
    getCommand find
    ${FIND} ${OGG_HOME} -type f \( -name '*.so*' -o -not -name '*.*' \) -exec chmod +x {} \;
}


function isOGGRunning {
    getCommand pgrep
    ${PGREP} -f ${OGGProcesses} &>/dev/null
}

function createSubdirs {
    echo "CREATE SUBDIRS" | ${runAsUser} ${OGG_HOME}/ggsci
}

function createGlobals {
    if [[ ! -f ${OGG_HOME}/GLOBALS ]]; then
        ${runAsUser} bash -c "echo GGSCHEMA C##OGGADMIN > ${OGG_HOME}/GLOBALS"
    else
        return 0
    fi
}

function initShell {
    if (! grep OGG_ETC_HOME "/home/oracle/.bash_profile" 2>/dev/null ); then
        cat<<EOF | ${runAsUser} bash -c 'cat >> /home/oracle/.bash_profile'
export OGG_HOME="${OGG_HOME}"
export ORACLE_HOME="${ORACLE_HOME}"
export ORACLE_SID="${ORACLE_SID}"
export TNS_ADMIN="${ORACLE_HOME}/network/admin"
export ORA_INVENTORY="${ORA_INVENTORY}"
export LD_LIBRARY_PATH="/usr/lib/jvm/jre/lib/amd64/server:${LD_LIBRARY_PATH}"
export PYTHONHOME="${OGG_HOME}/dirprm"
EOF
    fi
}

function startManager {
    local rptFile="${OGG_HOME}/dirrpt/MGR.rpt"
    local prmFile="${OGG_HOME}/dirprm/MGR.prm"
    ${runAsUser}   ${OGG_HOME}/mgr PARAMFILE ${prmFile} REPORTFILE ${rptFile} &>/dev/null &
    tailReport     ${rptFile}
}

function terminateGoldengate {
    echo -e "\nTerminating..."
    echo "Stop ER * !" | ${runAsUser} ${OGG_HOME}/ggsci
    sleep 5
    echo "Stop MGR  !" | ${runAsUser} ${OGG_HOME}/ggsci
    sleep 5
    exit 1
}

trap 