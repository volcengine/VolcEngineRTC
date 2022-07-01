const path = require('path')
const fse = require('fs-extra');
const rimraf = require('rimraf');

const srcDir = path.join(__dirname, '/../node_modules/@byted/vertc-electron-sdk/build');
const destDir = path.join(__dirname, '/../app/@byted/vertc-electron-sdk/build');

function main() {
    console.log('copySdkAddon, srcDir: ', srcDir);
    console.log('copySdkAddon, destDir: ', destDir);

    if (process.platform === "darwin") {
        rimraf.sync(destDir);
    }
    fse.mkdirsSync(destDir);

    // To copy a folder or file
    fse.copySync(srcDir, destDir, { overwrite: true }, function (err) {
        if (err) {
            // console.error(err);      |___{ overwrite: true } // add if you want to replace existing folder or file with same name
            console.error('copy sdk addon, error: ', err);
        } else {
            console.log("copy sdk addon, success!");
        }
    });
}

//////////////////////////////////////////////////
main();