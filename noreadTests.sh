echo "NOREAD WITHOUT SPLAY"
echo "Running uniform"
./jitd_noread testscripts/noreadWithoutSplay/uniform > output/noreadWithoutSplay/uniform
echo "Running heavyhitter"
./jitd_noread testscripts/noreadWithoutSplay/heavyhitter > output/noreadWithoutSplay/heavyhitter
echo "Running uniform to heavyhitter"
./jitd_noread testscripts/noreadWithoutSplay/uniformToHeavyhitter > output/noreadWithoutSplay/uniformToHeavyhitter
echo "Running heavyhitter to uniform"
./jitd_noread testscripts/noreadWithoutSplay/heavyhitterToUniform > output/noreadWithoutSplay/heavyhitterToUniform
echo "Running heavyhitter to heavyhiiter"
./jitd_noread testscripts/noreadWithoutSplay/heavyhitterToHeavyhitter > output/noreadWithoutSplay/heavyhitterToHeavyhitter