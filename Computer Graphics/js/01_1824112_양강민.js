var scene = new THREE.Scene();
var renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.shadowMap.enabled = true;
var camera = new THREE.PerspectiveCamera(30, 1.0, 0.1, 1000);
var controls = new THREE.OrbitControls(camera, renderer.domElement);

//Lights
const pointLight1 = new THREE.PointLight(0xff0000, 0.9, 15, 3);
const pointLight2 = new THREE.PointLight(0x00ff00, 0.9, 15, 3);
const pointLight3 = new THREE.PointLight(0x0000ff, 0.9, 15, 3);
const pointLight4 = new THREE.PointLight(0xffffff, 0.9, 15, 3);

var gui = new dat.GUI();

function initLight() {
  pointLight1.position.set(-2, -2, 2);
  scene.add(pointLight1);

  pointLight2.position.set(2, -2, 2);
  scene.add(pointLight2);

  pointLight3.position.set(2, 2, 2);
  scene.add(pointLight3);

  pointLight4.position.set(-2, 2, 2);
  scene.add(pointLight4);
}

function initGeometry() {
  const axesHelper = new THREE.AxesHelper();
  scene.add(axesHelper);

  var material0 = new THREE.MeshLambertMaterial({
    color: "#ffffff",
    side: THREE.DoubleSide,
  });
  var geometryPlane = new THREE.PlaneGeometry(10, 10);
  var plane = new THREE.Mesh(geometryPlane, material0);
  plane.receiveShadow = true;
  scene.add(plane);

  var plane = new THREE.Mesh(geometryPlane, material0);
  plane.receiveShadow = true;
  plane.translateY(5.0);
  plane.translateZ(5.0);
  plane.rotateX(Math.PI * 0.5);
  scene.add(plane);

  var plane = new THREE.Mesh(geometryPlane, material0);
  plane.receiveShadow = true;
  plane.translateX(-5.0);
  plane.translateZ(5.0);
  plane.rotateY(Math.PI * 0.5);
  scene.add(plane);

  const geometry1 = new THREE.TorusGeometry(1.0, 0.6);
  const material1 = new THREE.MeshStandardMaterial({ color: 0xffffff });
  const torus1 = new THREE.Mesh(geometry1, material1);
  torus1.translateZ(0.0);
  scene.add(torus1);

  const geometry2 = new THREE.TorusGeometry(0.8, 0.5);
  const material2 = new THREE.MeshStandardMaterial({ color: 0xffffff });
  const torus2 = new THREE.Mesh(geometry2, material2);
  torus2.translateZ(0.5);
  scene.add(torus2);

  const geometry3 = new THREE.TorusGeometry(0.6, 0.4);
  const material3 = new THREE.MeshStandardMaterial({ color: 0xffffff });
  const torus3 = new THREE.Mesh(geometry3, material3);
  torus3.translateZ(1.0);
  scene.add(torus3);

  const geometry4 = new THREE.TorusGeometry(0.4, 0.3);
  const material4 = new THREE.MeshStandardMaterial({ color: 0xffffff });
  const torus4 = new THREE.Mesh(geometry4, material4);
  torus4.translateZ(1.5);
  scene.add(torus4);

  const geometry5 = new THREE.CylinderGeometry(0.5, 0.5);
  const material5 = new THREE.MeshStandardMaterial({ color: 0xffffff });
  const cylinder1 = new THREE.Mesh(geometry5, material5);
  cylinder1.translateX(3);
  cylinder1.translateY(-3);
  cylinder1.translateZ(0.5);
  cylinder1.rotateX(Math.PI * 0.5);
  scene.add(cylinder1);

  const geometry6 = new THREE.CylinderGeometry(0.5, 0.5);
  const material6 = new THREE.MeshStandardMaterial({ color: 0xffffff });
  const cylinder2 = new THREE.Mesh(geometry6, material6);
  cylinder2.translateX(-3);
  cylinder2.translateY(3);
  cylinder2.translateZ(0.5);
  cylinder2.rotateX(Math.PI * 0.5);
  scene.add(cylinder2);

  const geometry7 = new THREE.ConeGeometry(0.5, 1.0);
  const material7 = new THREE.MeshStandardMaterial({ color: 0xffffff });
  const cone1 = new THREE.Mesh(geometry7, material7);
  cone1.translateX(3);
  cone1.translateY(3);
  cone1.translateZ(0.5);
  cone1.rotateX(Math.PI * 0.5);
  scene.add(cone1);

  const geometry8 = new THREE.ConeGeometry(0.5, 1.0);
  const material8 = new THREE.MeshStandardMaterial({ color: 0xffffff });
  const cone2 = new THREE.Mesh(geometry8, material8);
  cone2.translateX(-3);
  cone2.translateY(-3);
  cone2.translateZ(0.5);
  cone2.rotateX(Math.PI * 0.5);
  scene.add(cone2);
}

function initRenderer() {
  camera.position.x = 15;
  camera.position.y = -15;
  camera.position.z = 15;
  camera.up.x = 0;
  camera.up.y = 0;
  camera.up.z = 1;
  controls.update();
  renderer.setClearColor("#000000");
  renderer.setSize(500, 500);
  // Append Renderer to DOM
  document.body.appendChild(renderer.domElement);
}

function initGUI() {
  gui.add(pointLight1, "visible").name("P1 Light");
  gui.add(pointLight2, "visible").name("P2 Light");
  gui.add(pointLight3, "visible").name("P3 Light");
  gui.add(pointLight4, "visible").name("P4 Light");
}

function init() {
  initLight();
  initGeometry();
  initRenderer();
  initGUI();
  console.log("[01-quiz]");
  console.log(scene.children);
}

// Render Loop
var render = function () {
  requestAnimationFrame(render);
  controls.update();
  renderer.render(scene, camera);
};

init();
render();
