const modal = document.querySelector('.modal');
const overlay = document.querySelector('.overlay');
const openModalBtn = document.querySelector('.btn-open');
const closeModalBtn = document.querySelector('.btn-close');
const autoPlayBtn = document.querySelector('.autoPlayBtn');

const closeModal = function () {
  console.log('----closeModal----');
  modal.classList.add('hidden');
  overlay.classList.add('hidden');
};

autoPlayBtn.addEventListener('click', function () {
  closeModal();
  rtc.handleAutoPlay();
});

const openModal = function () {
  modal.classList.remove('hidden');
  overlay.classList.remove('hidden');
};
