import { exampleGroups } from './examples';

Page({
  data: {
    title: 'Api Example',

    exampleGroups,
  },

  handleViewExample(e: { target: { dataset: Record<string, any> } }) {
    const path = e.target.dataset.path;
    console.log('goto', path);

    tt.navigateTo({
      url: path,

      fail(e) {
        console.error('error', e);
      }
    });
  }
});
