#!/bin/bash
filename="$1"
t="$2"
expire="date -d + $2 min +%s"
while read -r i
do
	ADDR=$i

	/sbin/iptables -t filter -I INPUT -s $ADDR -m comment --comment "$expire" -j DROP
	/sbin/iptables -t filter -I OUTPUT -s $ADDR -m comment --comment "$expire" -j DROP
	/sbin/iptables -t filter -I FORWARD -s $ADDR -m comment --comment "$expire" -j DROP
	/sbin/iptables -t filter -I INPUT -d $ADDR -m comment --comment "$expire" -j REJECT
	/sbin/iptables -t filter -I OUTPUT -d $ADDR -m comment --comment "$expire" -j REJECT
	/sbin/iptables -t filter -I FORWARD -d $ADDR -m comment --comment "$expire" -j REJECT

	echo "Block ALL INPUT from " $ADDR " net DROPPED."
done < "$filename"
