let c = document.getElementById("myCanvas");
let ctx = c.getContext("2d");
let xValue = 50;
let yValue = 200;

let boxPts = [];
let movePts = [];

boxPts.push(new THREE.Vector2(150, 150));
boxPts.push(new THREE.Vector2(350, 350));

boxPts.push(new THREE.Vector2(0, 0));
boxPts.push(new THREE.Vector2(100, 100));

boxPts.push(new THREE.Vector2(400, 400));
boxPts.push(new THREE.Vector2(450, 450));

boxPts.push(new THREE.Vector2(100, 100));
boxPts.push(new THREE.Vector2(200, 200));

boxPts.push(new THREE.Vector2(450, 450));
boxPts.push(new THREE.Vector2(500, 500));

movePts.push(new THREE.Vector2(xValue, yValue));
movePts.push(new THREE.Vector2(xValue + 50, yValue + 50));

function draw_box(minPt, maxPt, isFill) {
  ctx.beginPath();
  ctx.rect(minPt.x, minPt.y, maxPt.x - minPt.x, maxPt.y - minPt.y);
  if (isFill) ctx.fill();
  else ctx.stroke();
}

function draw_image() {
  let isFill = false;

  for (let i = 0; i < boxPts.length; i += 2) {
    if (box_box_collision(boxPts[i], boxPts[i + 1], movePts[0], movePts[1]))
      isFill = true;

    ctx.strokeStyle = "green";
    ctx.fillStyle = "green";
    draw_box(boxPts[i], boxPts[i + 1], isFill);

    ctx.strokeStyle = "red";
    ctx.fillStyle = "red";
    draw_box(movePts[0], movePts[1], isFill);

    isFill = false;
  }
}

function box_box_collision(pMin, pMax, qMin, qMax) {
  let pw = pMax.x - pMin.x;
  let qw = qMax.x - qMin.x;
  let ph = pMax.y - pMin.y;
  let qh = qMax.y - qMin.y;

  let collision = false;

  if (
    pMin.x < qMin.x + qw &&
    pMin.x + pw > qMin.x &&
    pMin.y < qMin.y + qh &&
    pMin.y + ph > qMin.y
  ) {
    collision = true;
  }

  if (collision) return true;
  return false;
}

//Keyboard Input
function keyDown(e) {
  if (e.key === "ArrowRight" || e.key === "Right") {
    xValue += 5;
  } else if (e.key === "ArrowLeft" || e.key === "Left") {
    xValue -= 5;
  } else if (e.key === "ArrowUp" || e.key === "Up") {
    yValue -= 5;
  } else if (e.key === "ArrowDown" || e.key === "Down") {
    yValue += 5;
  }

  movePts[0].x = xValue;
  movePts[1].x = xValue + 50;
  movePts[0].y = yValue;
  movePts[1].y = yValue + 50;
}

//Animation Callback
function clear() {
  ctx.clearRect(0, 0, c.width, c.height);
}
function update() {
  clear();
  draw_image();
  requestAnimationFrame(update);
}
update();
document.addEventListener("keydown", keyDown);
