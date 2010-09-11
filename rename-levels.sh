#!/bin/sh

if [[ -z "$1" ]]; then
	echo "A directory must be given" >&2
	exit 1
fi

cd "$1/level"
mv racing.lvl 2racing1.lvl

for X in "bathhouse sumo" "field football" "amber greed" "fight duel" "colvs collection" dragster; do
	OLD="${X% *}"
	NEW="${X#* }"

	for N in "" 2 3 4; do
		mv "${OLD}${N}.lvl" "2${NEW}${N:-1}.lvl"
	done
done

for X in "bath sumo" "field football"; do
	OLD="${X% *}"
	NEW="${X#* }"

	for N in "" 2; do
		mv "4${OLD}${N}.lvl" "4${NEW}${N:-1}.lvl"
	done
done

exit 0
