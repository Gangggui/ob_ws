
### 自带装饰器

```
1. Inverter（反转器）：将子节点的返回值进行取反，即如果子节点返回成功，则返回失败，反之亦然。

2. Succeeder（成功器）：无论子节点返回什么，都将返回成功。

3. Repeater（重复器）：重复执行子节点直到满足某个条件。

4. UntilFail（直到失败）：重复执行子节点直到其返回失败。

5. UntilSuccess（直到成功）：重复执行子节点直到其返回成功。

6. Timeout（超时）：在规定时间内执行子节点，如果时间到了仍未完成，则返回失败。

7. MaxTime（最大时间）：执行子节点，但最长执行时间不能超过规定值，超过则返回失败。

8. AlwaysSuccess（总是成功）：无论子节点返回什么，都将返回成功。

9. AlwaysFail（总是失败）：无论子节点返回什么，都将返回失败。

10. InSequence（顺序执行）：按顺序执行子节点，如果其中一个返回失败，则停止执行并返回失败。

11. InParallel（并行执行）：同时执行多个子节点，可以设置成功或失败的条件。

12. Random（随机执行）：随机选择一个子节点进行执行。

13. DynamicPriority（动态优先级）：按照子节点的优先级进行执行，可以动态调整优先级。

14. MemSequence（记忆顺序执行）：按照顺序执行子节点，如果其中一个返回失败，则记住当前位置，下次从该位置开始执行。

15. MemPriority（记忆优先级执行）：按照优先级执行子节点，如果其中一个返回成功，则记住当前位置，下次从该位置开始执行。
```


要将C++程序中定义的动作节点与behavior-tree库中的TreeNodesModel标签绑定，需要进行以下步骤：

1. 定义动作节点

在C++程序中定义一个继承自BehaviorTree::ActionNodeBase的动作节点，例如：

```
class MyActionNode : public BehaviorTree::ActionNodeBase
{
public:
    MyActionNode(const std::string& name)
        : ActionNodeBase(name, {})
    {}

    BehaviorTree::NodeStatus tick() override
    {
        // 执行动作
        return BehaviorTree::NodeStatus::SUCCESS;
    }
};
```

2. 在TreeNodesModel标签中添加节点

在TreeNodesModel标签中添加一个节点，例如：

```
<TreeNodesModel>
    <ActionNodeModel name="my_action_node" category="action"/>
</TreeNodesModel>
```

3. 绑定节点

在C++程序中，使用BehaviorTree::Factory注册节点，并将其与TreeNodesModel标签中的节点绑定，例如：

```
BehaviorTree::Factory factory;
factory.registerNodeType<MyActionNode>("MyActionNode");
factory.registerSimpleCondition("my_condition", std::bind(&MyCondition::check, &my_condition));
factory.registerFromPlugin("libmy_plugin.so");
BehaviorTree::Parser parser(factory);

// 将TreeNodesModel标签中的节点与动作节点绑定
parser.idMapping("my_action_node", "MyActionNode");

// 加载行为树
auto tree = parser.parseFile("my_tree.xml");
```

在绑定节点之后，可以使用TreeNodesModel标签中的节点名称（例如"my_action_node"）来引用动作节点。在行为树中使用节点名称时，BehaviorTree库会自动将其映射到对应的动作节点。