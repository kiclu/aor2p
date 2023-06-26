sum_s3=0

for i in {1..100}
do
    cur=$(./aor2p $@ -s3 | grep 'time taken' | awk '{print $3}' | rev | cut -c 3- | rev)
    sum_s3=$(( $sum_s3 + $cur ))
done

echo "time total: "$sum_s3
