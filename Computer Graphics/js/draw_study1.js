var scene = new THREE.Scene();
var renderer = new THREE.WebGLRenderer({ antialias: true });
var camera = new THREE.PerspectiveCamera(30, 1.0, 0.1, 1000);
// var camera = new THREE.OrthographicCamera(-10, 3, 3, -3, -10, 10);

function initRenderer() {
  camera.position.z = 4;
  renderer.setClearColor("#000000");
  renderer.setSize(500, 500);

  document.body.appendChild(renderer.domElement);
}

function initGeometry() {
  const axesHelper = new THREE.AxesHelper();
  scene.add(axesHelper);

  var material0 = new THREE.MeshBasicMaterial({ color: "#0000ff" });
  var material1 = new THREE.MeshBasicMaterial({ color: "#ff0000" });
  material0.wireframe = true;
  material1.wireframe = true;

  var geometryCube = new THREE.BoxGeometry(1, 1, 1);
  var cube0 = new THREE.Mesh(geometryCube, material0);
  var cube1 = new THREE.Mesh(geometryCube, material1);

  cube0.translateX(0.5);
  cube0.translateZ(-0.5);
  cube1.translateZ(-4.0);

  scene.add(cube0);
  scene.add(cube1);
}

function init() {
  initRenderer();
  initGeometry();
}

var render = function () {
  renderer.render(scene, camera);
};

init();
render();
