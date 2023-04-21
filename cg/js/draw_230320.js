let c = document.getElementById("myCanvas");
let ctx = c.getContext("2d");
let xValue = 0;
let yValue = 0;

//Make data
let linePts = [];
linePts.push(new THREE.Vector2(0, 0));
linePts.push(new THREE.Vector2(250, 250));

linePts.push(new THREE.Vector2(0, 100));
linePts.push(new THREE.Vector2(400, 200));

let boxPts = [];

boxPts.push(new THREE.Vector2(100, 100));
boxPts.push(new THREE.Vector2(300, 300));


function draw_line(p0, p1) {
    ctx.beginPath();
    ctx.moveTo(p0.x, p0.y);
    ctx.lineTo(p1.x, p1.y);
    ctx.stroke();
}

function draw_point(p) {
    ctx.fillStyle = "#ff0000";
    ctx.beginPath();
    ctx.arc(p.x, p.y, 5, 0, 2 * Math.PI);
    ctx.fill();
}

function draw_box(minPt, maxPt) {
    let p0 = new THREE.Vector2(minPt.x, minPt.y);
    let p1 = new THREE.Vector2(minPt.x, maxPt.y);
    let p2 = new THREE.Vector2(maxPt.x, maxPt.y);
    let p3 = new THREE.Vector2(maxPt.x, minPt.y);
    draw_line(p0, p1);
    draw_line(p1, p2);
    draw_line(p2, p3);
    draw_line(p3, p0);
}

function draw_circle(ctr, radius) {
    ctx.beginPath();
    ctx.arc(ctr.x, ctr.y, radius, 0, 2 * Math.PI);
    ctx.stroke();
}

function draw_image() {
    ctx.strokeStyle = "blue";
    draw_line(linePts[0], linePts[1]);
    ctx.strokeStyle = "red";
    draw_line(linePts[2], linePts[3]);

    line_line_intersection(linePts[0], linePts[1], linePts[2], linePts[3]);

    ctx.strokeStyle = "green";
    draw_box(boxPts[0], boxPts[1])

    line_box_intersection(linePts[0], linePts[1], boxPts[0], boxPts[1]);
    line_box_intersection(linePts[2], linePts[3], boxPts[0], boxPts[1]);

    ctx.strokeStyle = "black";
    draw_circle(new THREE.Vector2(230 + xValue, 230 + yValue), 110);

    line_circle_intersection(linePts[0], linePts[1], new THREE.Vector2(230 + xValue, 230 + yValue), 110);
    line_circle_intersection(linePts[2], linePts[3], new THREE.Vector2(230 + xValue, 230 + yValue), 110);

    box_circle_intersection(boxPts[0], boxPts[1], new THREE.Vector2(230 + xValue, 230 + yValue), 110);
}

function line_line_intersection(p0, p1, p2, p3) {
    // y=ax+b : 직선의 방정식
    // a:기울기 : y증가량 / x증가량
    // y=a0x+b0  y=a1x+b1

    if (p1.x - p0.x == 0 && p3.x - p2.x != 0) {
        //선분1 기울기 = 0
        let a1 = (p3.y - p2.y) / (p3.x - p2.x);
        let b1 = p2.y - a1 * p2.x;

        let intersectionX = p0.x;
        let intersectionY = a1 * intersectionX + b1;

        if (p2.x > intersectionX || p3.x < intersectionX) return;
        if (p2.y > intersectionY || p3.y < intersectionY) return;

        let intersectionPt = new THREE.Vector2(intersectionX, intersectionY);
        draw_point(intersectionPt);
    } else if (p1.x - p0.x != 0 && p3.x - p2.x == 0) {
        //선분2 기울기 = 0
        let a0 = (p1.y - p0.y) / (p1.x - p0.x);
        let b0 = p0.y - a0 * p0.x;

        let intersectionX = p2.x;
        let intersectionY = a0 * p2.x + b0;

        if (p0.x > intersectionX || p1.x < intersectionX) return;
        if (p0.y > intersectionY || p1.y < intersectionY) return;

        let intersectionPt = new THREE.Vector2(intersectionX, intersectionY);
        draw_point(intersectionPt);
    } else if (p1.x - p0.x == 0 && p3.x - p2.x == 0) {
        //둘다 기울기가 없는 경우
    } else {
        let a0 = (p1.y - p0.y) / (p1.x - p0.x);
        let b0 = p0.y - a0 * p0.x;

        let a1 = (p3.y - p2.y) / (p3.x - p2.x);
        let b1 = p2.y - a1 * p2.x;

        //직선의 교점? a0x+b0=a1x+b1 --> (a0-a1)x = b1 -b0
        let intersectionX = (b1 - b0) / (a0 - a1);
        let intersectionY = a0 * intersectionX + b0;

        if (p0.x > intersectionX || p1.x < intersectionX) return;
        if (p2.x > intersectionX || p3.x < intersectionX) return;
        if (p0.y > intersectionY || p1.y < intersectionY) return;
        if (p2.y > intersectionY || p3.y < intersectionY) return;

        let intersectionPt = new THREE.Vector2(intersectionX, intersectionY);
        draw_point(intersectionPt);
    }
}

function line_box_intersection(lineP0, lineP1, boxMinPt, boxMaxPt) {
    let p0 = new THREE.Vector2(boxMinPt.x, boxMinPt.y);
    let p1 = new THREE.Vector2(boxMaxPt.x, boxMinPt.y);
    let p2 = new THREE.Vector2(boxMaxPt.x, boxMaxPt.y);
    let p3 = new THREE.Vector2(boxMinPt.x, boxMaxPt.y);

    line_line_intersection(lineP0, lineP1, p0, p1);
    line_line_intersection(lineP0, lineP1, p1, p2);
    line_line_intersection(lineP0, lineP1, p2, p3);
    line_line_intersection(lineP0, lineP1, p3, p0);
}

function line_circle_intersection(lineP0, lineP1, circleCtr, circleRadius) {
    // y=ax+b : 직선의 방정식
    let a0 = (lineP1.y - lineP0.y) / (lineP1.x - lineP0.x);
    let b0 = lineP0.y - a0 * lineP0.x;

    // ax^2+bx+c=0
    let a = 1 + (a0 * a0);
    let b = (-2 * circleCtr.x) + (2 * a0 * b0) - (2 * a0 * circleCtr.y);
    let c = (circleCtr.x * circleCtr.x) + (b0 * b0) - (2 * b0 * circleCtr.y) + (circleCtr.y * circleCtr.y) - (circleRadius * circleRadius);

    // 판별식
    let d = (b * b) - (4 * a * c);

    if (d < circleRadius) {
        // 만나는 점이 없음.
        return;
    }
    else if (d == circleCtr) {
        // 만나는 점이 1개

        if (lineP1.x - lineP0.x == 0) {
            // y축과 평행
            let intersectionX = lineP0.x;
            let intersectionY = a0 * intersectionX + b0;

            if (lineP0.x <= intersectionX && lineP1.x >= intersectionX && lineP0.y <= intersectionY && lineP1.y >= intersectionY) {
                let intersectionPt = new THREE.Vector2(intersectionX, intersectionY);
                draw_point(intersectionPt);
            }
        }
        else if (lineP1.y - lineP0.y == 0) {
            // x축과 평행
            let intersectionY = lineP0.y;
            let intersectionX = (intersectionY - b0) / a0;

            if (lineP0.x <= intersectionX && lineP1.x >= intersectionX && lineP0.y <= intersectionY && lineP1.y >= intersectionY) {
                let intersectionPt = new THREE.Vector2(intersectionX, intersectionY);
                draw_point(intersectionPt);
            }
        }
        else {
            let intersectionX = (-b) / (2 * a);
            let intersectionY = a0 * intersectionX + b0;

            if (lineP0.x <= intersectionX && lineP1.x >= intersectionX && lineP0.y <= intersectionY && lineP1.y >= intersectionY) {
                let intersectionPt = new THREE.Vector2(intersectionX, intersectionY);
                draw_point(intersectionPt);
            }
        }
    }
    else {
        // 만나는 점이 2개

        if (lineP1.x - lineP0.x == 0) {
            // y축과 평행
            let intersectionX1 = lineP0.x;
            let intersectionY1 = circleCtr.y + Math.sqrt(circleRadius * circleRadius - (intersectionX1 - circleCtr.x) * (intersectionX1 - circleCtr.x))

            if (lineP0.y <= intersectionY1 && lineP1.y >= intersectionY1) {
                let intersectionPt1 = new THREE.Vector2(intersectionX1, intersectionY1);
                draw_point(intersectionPt1);
            }

            let intersectionX2 = lineP0.x;
            let intersectionY2 = circleCtr.y - Math.sqrt(circleRadius * circleRadius - (intersectionX2 - circleCtr.x) * (intersectionX2 - circleCtr.x))

            if (lineP0.y <= intersectionY2 && lineP1.y >= intersectionY2) {
                let intersectionPt2 = new THREE.Vector2(intersectionX2, intersectionY2);
                draw_point(intersectionPt2);
            }
        }
        else if (lineP1.y - lineP0.y == 0) {
            // x축과 평행
            let intersectionY1 = lineP0.y;
            let intersectionX1 = circleCtr.x + Math.sqrt(circleRadius * circleRadius - (intersectionY1 - circleCtr.y) * (intersectionY1 - circleCtr.y));

            if (lineP0.x <= intersectionX1 && lineP1.x >= intersectionX1) {
                let intersectionPt1 = new THREE.Vector2(intersectionX1, intersectionY1);
                draw_point(intersectionPt1);
            }

            let intersectionY2 = lineP0.y;
            let intersectionX2 = circleCtr.x - Math.sqrt(circleRadius * circleRadius - (intersectionY2 - circleCtr.y) * (intersectionY2 - circleCtr.y));

            if (lineP0.x <= intersectionX2 && lineP1.x >= intersectionX2) {
                let intersectionPt2 = new THREE.Vector2(intersectionX2, intersectionY2);
                draw_point(intersectionPt2);
            }
        }
        else {
            let intersectionX1 = (-b + Math.sqrt(d)) / (2 * a);
            let intersectionY1 = a0 * intersectionX1 + b0;

            if (lineP0.x <= intersectionX1 && lineP1.x >= intersectionX1 && lineP0.y <= intersectionY1 && lineP1.y >= intersectionY1) {
                let intersectionPt1 = new THREE.Vector2(intersectionX1, intersectionY1);
                draw_point(intersectionPt1);
            }

            let intersectionX2 = (-b - Math.sqrt(d)) / (2 * a);
            let intersectionY2 = a0 * intersectionX2 + b0;

            if (lineP0.x <= intersectionX2 && lineP1.x >= intersectionX2 && lineP0.y <= intersectionY2 && lineP1.y >= intersectionY2) {
                let intersectionPt2 = new THREE.Vector2(intersectionX2, intersectionY2);
                draw_point(intersectionPt2);
            }
        }
    }
}

function box_circle_intersection(boxMinPt, boxMaxPt, circleCtr, circleRadius) {
    let p0 = new THREE.Vector2(boxMinPt.x, boxMinPt.y);
    let p1 = new THREE.Vector2(boxMaxPt.x, boxMinPt.y);
    let p2 = new THREE.Vector2(boxMaxPt.x, boxMaxPt.y);
    let p3 = new THREE.Vector2(boxMinPt.x, boxMaxPt.y);

    line_circle_intersection(p0, p1, circleCtr, circleRadius);
    line_circle_intersection(p1, p2, circleCtr, circleRadius);
    line_circle_intersection(p3, p2, circleCtr, circleRadius);
    line_circle_intersection(p0, p3, circleCtr, circleRadius);
}

//Keyboard Input
function keyDown(e) {
    if (e.key === 'ArrowRight' || e.key === 'Right') {
        xValue += 5;
    } else if (e.key === 'ArrowLeft' || e.key === 'Left') {
        xValue -= 5;
    } else if (e.key === 'ArrowUp' || e.key === 'Up') {
        yValue -= 5;
    } else if (e.key === 'ArrowDown' || e.key === 'Down') {
        yValue += 5;
    }
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
document.addEventListener('keydown', keyDown);