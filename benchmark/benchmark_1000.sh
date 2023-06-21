sum_s0=0
sum_s3=0

for i in {1..1000}
do
    cur_s0=$(../aor2p $@ -s0 | grep 'time taken' | awk '{print $3}' | rev | cut -c 3- | rev)
    sum_s0=$(( $cur_s0 + $sum_s0 ))
done

for i in {1..1000}
do
    cur_s3=$(../aor2p $@ -s3 | grep 'time taken' | awk '{print $3}' | rev | cut -c 3- | rev)
    sum_s3=$(( $cur_s3 + $sum_s3 ))
done

echo $@ > benchmark.log
echo "-s0="$(( $sum_s0 / 1000 ))"ns" >> benchmark.log
echo "-s3="$(( $sum_s3 / 1000 ))"ns" >> benchmark.log
