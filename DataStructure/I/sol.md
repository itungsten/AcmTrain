# I.   ��ķ¶��ħ��Ԫ��

### �������⣺

INPUT��

��һ�� Ԫ������ n���۲����� k���������� m��

�ڶ��� k�й۲����ݣ�

������ m�β���

OUTPUT:

����ѯ�ʲ�����Ӧ��

### ˼·�ͽⷨ��

ͨ��tag-��Ȩ���鼯�˽�������ݽṹ�󣬲����˰���󣬷����ⲻ����pojʳ�������˸�����?��

��ͨ�Ĳ��鼯�ʹ�Ȩ���鼯��������;�ϵ�������Ҫ�Ǳ�ʾ�������ԭ��

��ͨ���鼯��һ�����ϱ�ʾһ�࣬��Ȩ���鼯��һ�����ϱ�ʾ������Թ�ϵ������������union��ʱ��ҲҪά������Թ�ϵ��

���ǲ��鼯���ǲ���û��ɾ�������ѵ�Ҫ�ÿɳ־û����ݽṹ���X�m��Ⱥ���ˡ�

�ȵȣ�tag���滹�����ߣ�����ɶ��˼�أ���ž��ǳ���һ��ʼ��֪���������룬���������뱣�����������мӹ�֮���������

������,�����ȰѲ�����¼������Ȼ���Ų������Ͱ�ɾ��ת��Ϊ�����Ĳ��ˡ�

������һ���ӣ��������˳�������x�����ǿ���ɾ����Σ��������⣬���ǿ���ά��һ��isDelete����֮��Ķ��������isDeleteΪfalse����ô����ɾ������¼���ٰ�isDelete�ĳ�true��������ԡ�

ϸ�ڿ����룬����ϸע�͡�

˳���²�һ�£�֮ǰʵ���������õ�vector��Ȼ��������WA�ˣ������ĳ�����͹���

���ڣ��ҵó�������ۣ�

1.Խ��Խ�����׳���

2.�Ҳ�����vector

### ʱ�临�Ӷȣ�

ֻʹ����·��ѹ���Ĳ��鼯�����β������Ӷ�Ϊ$O(\log(N))$,��ô��������ʱ�临�Ӷ�Ϊ$O(M\log(N))$

��Ȼ�����б�Ҫ�ĳ�ʼ��$O(N)$,��ô�ܸ��Ӷ�Ϊ

$O(M\log(N)+N)$

### �ռ临�Ӷȣ�

���߲����͹۲���Ŀ��Ҫ�ռ�

$O( N + M+K)$