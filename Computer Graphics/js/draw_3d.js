var scence = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 4;

var renderer = new THREE.WebGLRenderer({ antialias: true });

renderer.setClearColor("#000000");
renderer.setSize(window.innerWidth, window.innerHeight);

document.body.appendChild(renderer.domElement);

var material = new THREE.MeshBasicMaterial({ color: "#fed136" });
material.wireframe = true;

var geometryCube = new THREE.BoxGeometry(1, 1, 1);
var cube = new THREE.Mesh(geometryCube, material);

var geometryTorus = new THREE.TorusGeometry(1.0, 0.5, 16, 100);
var torus = new THREE.Mesh(geometryTorus, material);

// scence.add(cube);
scence.add(torus);

var render = function () {
    requestAnimationFrame(render);

    // cube.rotation.x += 0.01;
    // cube.rotation.y += 0.01;
    torus.rotation.x += 0.01;
    torus.rotation.y += 0.01;
    torus.rotation.z += 0.01;
    renderer.render(scence, camera);
}

render();