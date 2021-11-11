const { app, BrowserWindow } = require("electron");
const path = require("path");

app.on("ready", ()=>{
    createWindow();
});

app.on('window-all-closed', function () {
    if (process.platform !== 'darwin') app.quit()
})

async function createWindow() {
    try {

        const win = new BrowserWindow({
            width: 500,
            height: 500,
            frame: false
        })
    
        win.loadFile('./static/index.html')
    } catch (e) {
        console.error(e);
    }
}