//=============================================
// https request without client certificate
const https = require('https');

const options = {
    hostname: 'www.baidu.com',
    port: 443,
    path: '/',
    method: 'GET',
    // headers: {
    //     'Content-Type': 'application/x-www-form-urlencoded',
    //     'Content-Length': Buffer.byteLength(postData)
    //     },
    // auth : 'user:password',
    // key: fs.readFileSync('test/fixtures/keys/agent2-key.pem'),
    // cert: fs.readFileSync('test/fixtures/keys/agent2-cert.pem'),
};

const req = https.request(options, (res) => {
  console.log('状态码：', res.statusCode);
  console.log('请求头：', res.headers);

  res.on('data', (d) => {
    process.stdout.write(d);
  });
});

req.on('error', (e) => {
  console.error(e);
});
req.end();


//=============================================
// https get without client certificate

https.get('https://www.baidu.com/', (res) => {
  console.log('状态码：', res.statusCode);
  console.log('请求头：', res.headers);

  res.on('data', (d) => {
    process.stdout.write(d);
  });

}).on('error', (e) => {
  console.error(e);
});

//=============================================
// https request without client certificate
const https = require('https');

const options = {
    hostname: 'www.baidu.com',
    port: 443,
    path: '/',
    method: 'GET',
    // headers: {
    //     'Content-Type': 'application/x-www-form-urlencoded',
    //     'Content-Length': Buffer.byteLength(postData)
    //     },
    // auth : 'user:password',
    key: fs.readFileSync('test/fixtures/keys/agent2-key.pem'),
    cert: fs.readFileSync('test/fixtures/keys/agent2-cert.pem'),
};

const req = https.request(options, (res) => {
  console.log('状态码：', res.statusCode);
  console.log('请求头：', res.headers);

  res.on('data', (d) => {
    process.stdout.write(d);
  });
});

req.on('error', (e) => {
  console.error(e);
});
req.end();