var scene = new THREE.Scene();
var renderer = new THREE.WebGLRenderer({ antialias: true });
var camera = new THREE.PerspectiveCamera(75, 1.0, 0.1, 1000);

function initLight() {
  var pointLight = new THREE.PointLight(0xffffff);
  pointLight.position.set(10, 10, 10);
  pointLight.castShadow = true;
  scene.add(pointLight);
}

function initRenderer() {
  camera.position.z = 15;
  renderer.setClearColor("#FFFFFF");
  renderer.setSize(500, 500);
  // Append Renderer to DOM
  document.body.appendChild(renderer.domElement);
}
function initGeometry() {
  // const axesHelper = new THREE.AxesHelper(); //x:red y:green z:blue
  // scene.add(axesHelper);

  //   var material0 = new THREE.MeshLambertMaterial({ color: "#ff0000" });
  var geometryCube = new THREE.BoxGeometry(1, 1, 1);
  //   var geometryCube = new THREE.SphereGeometry(0.5);
  //   var geometryCube = new THREE.ConeGeometry(0.3, 0.5);

  var check = 0;

  for (var i = 0; i < 10; i++) {
    for (var j = 0; j < 10; j++) {
      var material0 = new THREE.MeshLambertMaterial({
        color: Math.random() * 0xffffff,
      });

      if (check >= 50) {
        material0.wireframe = true;
      }

      var cube = new THREE.Mesh(geometryCube, material0);
      //Translation
      //   cube.translateX(-4.0 + 2.0 * i);
      //   cube.translateY(-4.0 + 2.0 * j);
      cube.translateX(-9 + 2.0 * i);
      cube.translateY(-9 + 2.0 * j);
      // Add cube to Scene
      scene.add(cube);
      check++;
    }
  }
}

function init() {
  initLight();
  initRenderer();
  initGeometry();
}

// Render Loop
var render = function () {
  requestAnimationFrame(render);
  for (var i = 1; i < scene.children.length; i++) {
    scene.children[i].rotation.x += Math.random() / 10;
    scene.children[i].rotation.y += Math.random() / 10;
    scene.children[i].rotation.z += Math.random() / 10;
  }
  renderer.render(scene, camera);
};

init();
render();
