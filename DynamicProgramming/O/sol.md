# O. ����

### ˼·�ͽⷨ��

��ȷ����λDP�����⣬�����������Һú��˽�����������ӡ�

���ճ����˵���⣬�����Ʋ�Ҫ62��˼·������ǻ��ĵ���Ŀ����������������и߾��ȼ����������ͷ�ۣ����Ի���д����ֱ��ͳ�ƻ��Ĵ�����Ŀ��

һ�����ǻ��Ĵ���ôֻ��Ҫ����ǰ�ַ���ǰһ���ַ���ǰǰһ���ַ��Ƿ�͵�ǰ�ַ���ͬ����ô��Ҫ��������last2��last1

һ�����ǻ��Ĵ������ǵ�ǰ�ַ����빹�ɻ��Ĵ���������ǰ�ַ����ɻ��Ĵ���������Ҫһ��found����

��Ȼ����λ����Ҫһ��cnt��һ��limit������һ��lead����

**״̬��ʾ**��$dp[cnt][last2][last1][found]$����ʾ��ǰһ���ַ���last1��ǰǰ�ַ���last2����cntλ�����λ����û��limit�����µĻ��Ĵ���Ŀ

**״̬ת��**��
$$
dp[cnt][last2][last1][found][lead][limit]=\Sigma (dp[cnt-1][last1][i][found||i=last1||i=last2][lead \and i=0][limit \and i=up])
$$
**��ʼ״̬**��

$dp[0][][][][][found]=found$

**����˳��**��

�Բ��𣬼��仯��������Ϊ����Ϊ��



һ���ӣ����ȡģһ��Ҫ(x%MOD+MOD)%MOD����Ϊsolve(r)��ģMOD�����²�һ������solve(l)  5555555555



ֵ��ע����ǣ���λDP������DPʱ��û�����״̬��������������ԭ��һ������λDP�ǵ���ģ�����β���Ƕ���ģ������Ļ������������ص��ģ�����һ��ԭ���ǣ�limit����Ϊlimit�ھ�����Ͻ��йأ������ڼ��仯��ʱ��û�м������Ͻ��йصĲ��֣���ʵ���˼���Ŀɸ����ԡ�



ͬ��������ע�⵽����ݴ���û��ʹ�ã�lead�����������ֶ���ǰ�����Ϊ10�����Բ������ǰ�����ͻ��



ϸ�ڿ����룬��������ϸע��

### ʱ�临�Ӷȣ�

$O(log(R))$ ???���᲻�ᣬò����λDP�����ϲ���ʱ�临�Ӷȣ�������λ���У�

### �ռ临�Ӷȣ�

$O( L )$   LΪ��λ��Ŀ

����$O(\log(R))$