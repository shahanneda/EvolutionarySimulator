# git checkout master
git branch -D web
git checkout -b web
./emc_full_build.sh
cp build dist
cp web/index.html index.html
cp web/coi-serviceworker.min.js coi-serviceworker.min.js
rm .gitignore
mv .gitignore-web .gitignore
git add .
git commit -m "Built web"
git push
# git checkout master