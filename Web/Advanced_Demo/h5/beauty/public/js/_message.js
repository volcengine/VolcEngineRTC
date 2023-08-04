/* 构造函数 */
function Message() {}

/* 用于移除message */
Message.id = 0;
/**
 * 创建全局提示
 * @param {string} content 提示内容
 * @param {number} duration 持续时间
 * @param {string} type 提示类型
 */
Message.prototype.create = function (content, duration, type) {
  // svg太长，此处省略
  const icon = {
    success: `<svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
<path fill-rule="evenodd" clip-rule="evenodd" d="M12.0003 0.857178C18.1543 0.857178 23.1431 5.84601 23.1431 12C23.1431 18.1541 18.1543 23.1429 12.0003 23.1429C5.84625 23.1429 0.857422 18.1541 0.857422 12C0.857422 5.84601 5.84625 0.857178 12.0003 0.857178Z" fill="#00B42A"/>
<path fill-rule="evenodd" clip-rule="evenodd" d="M15.6315 8.62438L16.2006 9.10187C16.515 9.36544 16.556 9.834 16.2923 10.1483C16.2922 10.1483 16.2922 10.1484 16.292 10.1483L11.3238 16.0659C11.0599 16.3799 10.5914 16.4209 10.2771 16.1573L9.13896 15.2023L14.5848 8.71581C14.8487 8.40179 15.3172 8.36087 15.6315 8.62438Z" fill="white"/>
<path fill-rule="evenodd" clip-rule="evenodd" d="M7.23438 12.5507L7.73281 11.9972C8.003 11.6971 8.46341 11.6678 8.76945 11.9312L12.2636 14.9386L11.3129 16.0825C11.0507 16.398 10.5823 16.4412 10.2668 16.179C10.2629 16.1758 10.2591 16.1725 10.2552 16.1692L7.30004 13.6093C6.98994 13.3407 6.95632 12.8715 7.22494 12.5614C7.22805 12.5578 7.23119 12.5543 7.23438 12.5507Z" fill="white"/>
</svg>
`,
    error: `<svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
<path d="M12.0003 0.857178C18.1544 0.857178 23.1431 5.84601 23.1431 12C23.1431 18.1541 18.1544 23.1429 12.0003 23.1429C5.84625 23.1429 0.857422 18.1541 0.857422 12C0.857422 5.84601 5.84625 0.857178 12.0003 0.857178Z" fill="#F53F3F"/>
<path fill-rule="evenodd" clip-rule="evenodd" d="M15.2496 8.03572L15.992 8.77818C16.2263 9.0125 16.2263 9.3924 15.992 9.62671L13.605 12.0137L15.992 14.4006C16.2263 14.6349 16.2263 15.0148 15.992 15.2491L15.2496 15.9915C15.0152 16.2259 14.6353 16.2259 14.401 15.9915L12.0142 13.6046L9.62805 15.9907C9.39374 16.225 9.01384 16.225 8.77953 15.9907L8.03706 15.2482C7.80275 15.0139 7.80275 14.634 8.03706 14.3997L10.4233 12.0137L8.03706 9.62758C7.80275 9.39326 7.80275 9.01337 8.03706 8.77905L8.77953 8.03659C9.01384 7.80227 9.39374 7.80227 9.62805 8.03659L12.0142 10.4228L14.401 8.03572C14.6353 7.80141 15.0152 7.80141 15.2496 8.03572Z" fill="white"/>
</svg>
`,
    info: `<svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
<path fill-rule="evenodd" clip-rule="evenodd" d="M12.0003 0.857178C18.1544 0.857178 23.1431 5.84601 23.1431 12C23.1431 18.1541 18.1544 23.1429 12.0003 23.1429C5.84625 23.1429 0.857422 18.1541 0.857422 12C0.857422 5.84601 5.84625 0.857178 12.0003 0.857178Z" fill="#165DFF"/>
<path fill-rule="evenodd" clip-rule="evenodd" d="M12.8637 9.93991C13.0689 9.93991 13.2352 10.1062 13.2352 10.3113L13.2348 15.5564L14.3371 15.5567C14.5668 15.5567 14.7531 15.7429 14.7531 15.9727V17.3038C14.7531 17.5336 14.5668 17.7198 14.3371 17.7198H9.74803C9.51828 17.7198 9.33203 17.5336 9.33203 17.3038V15.9727C9.33203 15.7429 9.51828 15.5567 9.74803 15.5567L10.8585 15.5564V12.13L10.6443 12.1305C10.4145 12.1305 10.2283 11.9443 10.2283 11.7145V10.3616C10.2283 10.1319 10.4145 9.94561 10.6443 9.94561L11.1634 9.9459C11.185 9.94197 11.2073 9.93991 11.2301 9.93991H12.8637ZM12.646 6.29492C12.8758 6.29492 13.062 6.48117 13.062 6.71092V8.25606C13.062 8.48581 12.8758 8.67206 12.646 8.67206H11.1009C10.8712 8.67206 10.6849 8.48581 10.6849 8.25606V6.71092C10.6849 6.48117 10.8712 6.29492 11.1009 6.29492H12.646Z" fill="white"/>
</svg>
`,
    warning: `<svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
<path d="M12.0003 23.1429C18.1543 23.1429 23.1431 18.1541 23.1431 12C23.1431 5.846 18.1543 0.857178 12.0003 0.857178C5.84625 0.857178 0.857422 5.846 0.857422 12C0.857422 18.1541 5.84625 23.1429 12.0003 23.1429Z" fill="#FF7D00"/>
<path fill-rule="evenodd" clip-rule="evenodd" d="M12.8067 15.0026C13.1486 15.0026 13.4257 15.2798 13.4257 15.6217V17.2312C13.4257 17.5731 13.1486 17.8502 12.8067 17.8502H11.1972C10.8553 17.8502 10.5781 17.5731 10.5781 17.2312V15.6217C10.5781 15.2798 10.8553 15.0026 11.1972 15.0026H12.8067ZM12.8067 5.91064C13.1486 5.91064 13.4257 6.1878 13.4257 6.52969V13.0423C13.4257 13.3842 13.1486 13.6614 12.8067 13.6614H11.1972C10.8553 13.6614 10.5781 13.3842 10.5781 13.0423V6.52969C10.5781 6.1878 10.8553 5.91064 11.1972 5.91064H12.8067Z" fill="white"/>
</svg>
`,
  };
  const html = `
        <li class="message-item fade-in" data-id="${Message.id}">
            <div>
                ${icon[type]}
                <span>${content}</span>
            </div>
        </li>`;

  const messageUl = document.querySelector('ul.message-list');

  messageUl.insertAdjacentHTML('beforeend', html);
  Message.id++;
  const lis = document.querySelectorAll('li.message-item');
  const length = lis.length;
  const lastLi = lis[length - 1];
  // 延时移除
  lastLi._timeout = setTimeout(function () {
    lastLi.classList.remove('fade-in');
    lastLi.classList.add('fade-out');
    lastLi.addEventListener('animationend', function (e) {
      this.remove();
    });
  }, duration);
  // 最多显示7条
  if (length > 7) {
    clearTimeout(lis[0]._timeout);
    lis[0].remove();
  }
};
Message.prototype.success = function (content, duration = 3000) {
  this.create(content, duration, 'success');
  return Message.id;
};
Message.prototype.error = function (content, duration = 3000) {
  this.create(content, duration, 'error');
  return Message.id;
};
Message.prototype.warning = function (content, duration = 3000) {
  this.create(content, duration, 'warning');
  return Message.id;
};
Message.prototype.info = function (content, duration = 3000) {
  this.create(content, duration, 'info');
  return Message.id;
};
Message.prototype.loading = function (content, duration = 3000) {
  this.create(content, duration, 'loading');
  return Message.id;
};
Message.prototype.remove = function (id) {
  const li = document.querySelector(`li.message-item[data-id="${id}"]`);
  clearTimeout(li._timeout);
  li.remove();
};

window.Message = Message;

