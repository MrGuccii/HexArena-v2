const canvas = document.getElementById('hexArenaCanvas');
const ctx = canvas.getContext('2d');

// Canvas sizing to the entire window
function resize() {
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
}
window.addEventListener('resize', resize);
resize();

// Local mouse position
let mouseX = 0;
let mouseY = 0;

window.addEventListener('mousemove', (e) => {
    mouseX = e.clientX;
    mouseY = e.clientY;
});

// Position of the player on the server
let serverPlayerX = window.innerWidth / 2;
let serverPlayerY = window.innerHeight / 2;


// Connecting to the WebSocket server
const ws = new WebSocket('wss://localhost:7000');

ws.onopen = () => {
    console.log('Connected to the WebSocket server');

    // Start sending input to the server at 60 FPS
    setInterval(sendInput, 1000 / 60);
}

ws.onmessage = (event) => {
    try {
        const data = JSON.parse(event.data);
        if (data.x !== undefined && data.y !== undefined) {
            serverPlayerX = data.x;
            serverPlayerY = data.y;
        } else {
            console.error('Invalid data received from server:', data);
        }
    } catch (error) {
        console.error('Error parsing server message:', error);
    }
}

ws.onclose = () => console.log('Disconnected from the WebSocket server');
ws.onerror = (error) => console.error('WebSocket error:', error);

function sendInput() {
    if (ws.readyState === WebSocket.OPEN) {
        const data = {
            x: mouseX,
            y: mouseY
        };
        ws.send(JSON.stringify(data));
    }
}


function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    ctx.strokeStyle = '#333';
    ctx.lineWidth = 1;
    for (let i = 0; i < canvas.width; i += 50) {
        ctx.beginPath(); ctx.moveTo(i, 0); ctx.lineTo(i, canvas.height); ctx.stroke();
    }
    for (let i = 0; i < canvas.height; i += 50) {
        ctx.beginPath(); ctx.moveTo(0, i); ctx.lineTo(canvas.width, i); ctx.stroke();
    }

    ctx.fillStyle = 'white';
    ctx.textAlign = 'center';
    ctx.font = '24px Arial';
    ctx.fillText(`Server Position X: ${serverPlayerX}`, 150, 50);
    ctx.fillText(`Server Position Y: ${serverPlayerY}`, 150, 80);
    ctx.fillText(`Local Position X: ${mouseX}`, 150, 110);
    ctx.fillText(`Local Position Y: ${mouseY}`, 150, 140);

    requestAnimationFrame(draw);
}

draw();