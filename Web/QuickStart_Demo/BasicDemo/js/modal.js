/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

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
