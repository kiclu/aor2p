sum_s0=0
sum_s3=0

for i in {1..10}
do
    cur_s0=$(./aor2p $@ -s0 | grep 'time taken' | awk '{print $3}' | rev | cut -c 3- | rev)
    sum_s0=$(( $cur_s0 + $sum_s0 ))
done

for i in {1..10}
do
    cur_s3=$(./aor2p $@ -s3 | grep 'time taken' | awk '{print $3}' | rev | cut -c 3- | rev)
    sum_s3=$(( $cur_s3 + $sum_s3 ))
done

echo "-s0="$(( $sum_s0 / 10 ))"ns"
echo "-s3="$(( $sum_s3 / 10 ))"ns"
echo "relative="$(( $sum_s0 / $sum_s3 ))
