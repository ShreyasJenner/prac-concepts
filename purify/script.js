// create a flash on the screen
function triggerFlash() {
    let flash = document.getElementById('flashEffect');
    flash.style.animation = "flashEffect 0.2s ease-in-out";

    setTimeout(() => {flash.style.animation = "";}, 200);
}

// function to make the glowing circle slowly disappear
function disappearCircle() {
    let circle = document.getElementById('glowing-circle');
    circle.classList.add('animate');
}

// create splatters
function createSplatter(x, y) {
    for(let i = 0; i < 10; i++) {
        let splatter = document.createElement('div');
        splatter.classList.add('splatter');

        let size = Math.random() * 20 + 10;
        let offsetX = (Math.random() - 0.5) * 60;
        let offsetY = (Math.random() - 0.5) * 40;

        splatter.style.width = `${size}px`;
        splatter.style.height = `${size}px`;
        splatter.style.left = `${x + offsetX}px`;
        splatter.style.top = `${y + offsetY}px`;

        document.body.appendChild(splatter);

        setTimeout(() => splatter.remove(), 1500);
    }
}

document.addEventListener('click', (event) => {
    disappearCircle();
    triggerFlash();

    //createSplatter(event.clientX, event.clientY);
});

var video = document.getElementById('myvid');
function playvid() {
    myvid.play();
}

function pausevid() {
    myvid.pause()
}

