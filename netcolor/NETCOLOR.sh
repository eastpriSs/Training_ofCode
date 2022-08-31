
# --------------------------------------------------------- ^
#       NETCOLOR
#
#       ��������� ������� ���������� ����������
#       � ���� ����� � ������� � ������������ 
#       ����� �����
#
#       ����������� ����������: 
#       
#       1) �����, ����� � �������� �� ������� ������������.
#       2) �������, ������� ����� ������� � �������� ����.
# --------------------------------------------------------- ^






# *  --- ����� ��������� ��� ������������� -----------------------/
# *
# *                 ����� ����� ��������� �������� � ����������
# * 

# ================= ������ (�������� �������) :

HSMGR=()

#  ================ ���, ������, ������� - �� �����, ����� � ��������
#                   �� ������� �������� ����
HSMGR[0,0]=8   
HSMGR[0,1]=2
HSMGR[0,2]=3
#   ===============  ����� (���) '�������' ����� ������� � �������   
HSMGR[0,3]=55
HSMGR[0,4]=20



# *
# *     ����� ����� �������� ����� � ��� ID, ������ ��� ������
# *     ��������� � ���, ��� ���� ���� ������� � �������
# *
outputID () {
    echo "
     ---------*--*--------------*--*--------------*--*----
    |    ID:                    PLACE:                    |
    |     0                 Sanatoriy OB'                 |  
    
    
     -*-------------*-----------------------*-------------
    "
}
# *
# *  --------------------------------------------------------------\















# *  --- ����� ��������� ��� ���������� -----------------------/
# *
outputManual () {
    echo "
     __________________________________
    |        MANUAL                    |  
    |    print '-1' for exit           |    
    |    print '-2 '                 ? |
    |__________________________________|
    "
}


IDin=99 # ����
outputTimeTable () {
    
    # �������� ����� ���������
    HOUR=${HSMGR[ $IDin, 0   ]}   #  ��� 
    MINUTE=${HSMGR[ $IDin, 1 ]}   #  ������
    SECOND=${HSMGR[ $IDin, 2 ]}   #  �������
    GREEN=${HSMGR[ $IDin, 3  ]}   #  ������� ����
    RED=${HSMGR[ $IDin, 4    ]}   #  ������� ����
    
    # --------------------------------------------------------------------/
    #                   �����  =  8:0:0|55:22                       
    # --------------------------------------------------------------------\
    printf "$HOUR:$MINUTE:$SECOND" 
    echo   "|$GREEN:$RED"
    
    # ������� ����� ��������� �������� � �������� ��������� (���)
    # ���� �� +2 ���� � ����������
    
    timeSystemHour=$(date '+%H')
    diffTime=$(((timeSystemHour - HOUR) / 2 / 2 * 8 * 3600)) 
    
    for((originTime=0; originTime < diffTime; originTime+=$((GREEN+RED))))
    do
        
        # ��������� ������ # NEED REFACTORING ����� ������� ��������
        # � ��������� �������
        echo "GREEN -- $HOUR:$MINUTE:$SECOND +$GREEN sec" 
        
        if [ $((SECOND+GREEN)) -ge 60 ]
        then
            SECOND=$((SECOND + GREEN - 60))
            ((MINUTE+=1))
        else
            ((SECOND+=$GREEN))
        fi
        
        echo "RED -- $HOUR:$MINUTE:$SECOND +$RED sec"
        
        if [ $((SECOND+RED)) -ge 60 ]
        then
            SECOND=$((SECOND + RED - 60))
            ((MINUTE+=1))
        else
            ((SECOND+=$RED))
        fi
        
        # �������� ����. � ����� �� ������ ���������
        # ����� ������� ������ �����. � ����� ��� ������
        # (������� ��������) ����� ����� �����
        # ���������� ������ ��������� � ��������� ����������,
        # � ����� � ��������
        if [ $MINUTE -ge 60 ]
        then
            # MINUTE=$((MINUTE + localmin - 60)) ���, ��� �������
            MINUTE=0
            ((HOUR+=1))
        fi
        
        if [ $HOUR == 24 ]
        then
            HOUR=0
        fi
        
    done
    
    
}

# ����� �����
outputID
while [ 1==1 ]
do 
    outputManual
    
    printf "ID: "
    read IDin
    clear
    
    # ����� �� ���������
    if [ $IDin == -1 ] 
    then
        break
    fi
    
    outputID 
    outputTimeTable
done
# *  --------------------------------------------------------------\
