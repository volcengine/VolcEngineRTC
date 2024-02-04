export type IExampleGroup = {
  title: string;
  examples: IExample[];
}

export type IExample = {
  title: string;
  path: string;
}

export const exampleGroups: IExampleGroup[] = [
  {
    title: "基础功能",
    examples: [
      {
        title: '快速开始',
        path: '/pages/basic/quickstart/index',
      }
    ]
  }
]
